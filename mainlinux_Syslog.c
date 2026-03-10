#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Bu program, sistem günlüklerini (syslog) temsil eden verileri 
 Çift Yönlü Baðlý Liste (Doubly Linked List) yapýsýnda tutar.
 */

// --- VERÝ YAPISI TANIMLAMALARI ---

typedef struct LogNode {
    int logID;                 // Her log için benzersiz kimlik
    char timestamp[32];        // Olayýn gerçekleþme zamaný
    char priority[16];         // Öncelik seviyesi (INFO, ERROR, WARNING)
    char message[256];         // Log mesajý içeriði
    
    struct LogNode* next;      // Bir sonraki log kaydýna iþaretçi
    struct LogNode* prev;      // Bir önceki log kaydýna iþaretçi
} LogNode;

// --- FONKSÝYON PROTOTÝPLERÝ ---
LogNode* create_new_log(int id, const char* priority, const char* msg);
void add_log_to_end(LogNode** head, int id, const char* priority, const char* msg);
void display_logs_forward(LogNode* head);
void free_list(LogNode* head);
char* get_current_time();

// --- ANA PROGRAM ---
int main() {
    LogNode* syslog_list = NULL; // Listemizin baþlangýç noktasý (Head)

    printf("--- Linux Syslog Yonetim Sistemi Baslatiliyor ---\n\n");

    // Senaryo: Sisteme farklý önceliklerde loglar ekleniyor
    add_log_to_end(&syslog_list, 101, "INFO", "Sistem basariyla baslatildi.");
    add_log_to_end(&syslog_list, 102, "WARNING", "Disk doluluk orani %85 uzerinde.");
    add_log_to_end(&syslog_list, 103, "ERROR", "Kritik servis (nginx) durduruldu!");
    add_log_to_end(&syslog_list, 104, "INFO", "Kullanici 'Goknur' sisteme giris yapti.");

    // Loglarý ekrana yazdýr
    display_logs_forward(syslog_list);

    // Belleði temizle (Program kapanýrken sýzýntýlarý önlemek için)
    free_list(syslog_list);
    syslog_list = NULL;

    printf("\nProgram guvenli bir sekilde sonlandirildi.\n");
    return 0;
}

// --- FONKSÝYON DETAYLARI ---

/*
 brief Yeni bir log düðümü oluþturur ve bellekte yer ayýrýr.
 return Oluþturulan düðümün adresi.
 */
LogNode* create_new_log(int id, const char* priority, const char* msg) {
    LogNode* newNode = (LogNode*)malloc(sizeof(LogNode));
    if (newNode == NULL) {
        printf("Bellek hatasi: Yeni log olusturulamadi!\n");
        exit(1);
    }
    
    newNode->logID = id;
    strcpy(newNode->timestamp, get_current_time());
    strncpy(newNode->priority, priority, 15);
    strncpy(newNode->message, msg, 255);
    
    newNode->next = NULL;
    newNode->prev = NULL;
    
    return newNode;
}


 //brief Listeye sonradan ekleme yapar.
// Syslog mantýðýnda yeni log her zaman en sona eklenir.
 
void add_log_to_end(LogNode** head, int id, const char* priority, const char* msg) {
    LogNode* newNode = create_new_log(id, priority, msg);
    
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    
    LogNode* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next; // Listenin sonuna kadar git
    }
    
    temp->next = newNode;
    newNode->prev = temp; // Çift yönlü bað kuruluyor
}


// brief Tum listeyi bastan sona dogru ekrana yazdirir.
 
void display_logs_forward(LogNode* head) {
    if (head == NULL) {
        printf("Sistemde kayitli log bulunmamaktadir.\n");
        return;
    }
    
    printf("%-5s | %-20s | %-10s | %-30s\n", "ID", "ZAMAN", "SEVIYE", "MESAJ");
    printf("--------------------------------------------------------------------------\n");
    
    LogNode* current = head;
    while (current != NULL) {
        printf("%-5d | %-20s | %-10s | %-30s\n", 
               current->logID, current->timestamp, current->priority, current->message);
        current = current->next;
    }
}


 //brief Sistem saatini metin formatinda dondurur.
 
char* get_current_time() {
    time_t rawtime;
    struct tm* timeinfo;
    static char buffer[32];

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    
    return buffer;
}


 //brief Liste elemanlarini bellekten temizler.
 
void free_list(LogNode* head) {
    LogNode* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}
