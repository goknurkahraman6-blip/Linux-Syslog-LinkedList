# Linux Syslog Yönetimi ve Bağlı Liste Uygulaması

Bu proje, Kırklareli Üniversitesi Yazılım Mühendisliği bölümü **Veri Yapıları ve Algoritmalar** dersi kapsamında hazırlanmıştır. Projenin temel amacı, Linux işletim sistemindeki sistem günlüklerinin (syslog) yapısını analiz etmek ve bu verileri dinamik bir veri yapısı olan **Çift Yönlü Bağlı Liste** kullanarak yönetmektir.

---

### 1. Syslog Mekanizması Nedir? Ne İçin Kullanılır?
**Syslog**, Unix ve Linux tabanlı işletim sistemlerinde çekirdek, sistem servisleri ve uygulamalar tarafından üretilen tüm olayların (error, warning, info vb.) standart bir protokol üzerinden kaydedilmesini sağlayan mekanizmadır.
* **Kullanım Amacı:** Sistem hatalarının kaynağını bulmak (debugging), güvenlik denetimleri gerçekleştirmek, sistemin çalışma geçmişini analiz etmek ve kritik servislerin durumunu takip etmek için kullanılır.

### 2. Bağlı Liste ile Günlükler Nasıl Tutulur? Hangi Tür Tercih Edilmelidir?
Günlük kayıtları belirsiz sayıda ve sürekli akan veriler olduğu için sabit boyutlu diziler yerine, bellekten dinamik olarak yer ayıran **Bağlı Liste** yapısı kullanılır. Bu projede **Çift Yönlü Bağlı Liste (Doubly Linked List)** tercih edilmiştir. Bu yapıda her düğüm, kendisinden önceki ve sonraki kaydın adresini (pointer) saklar.

### 3. Seçilen Bağlı Liste Türünün Tercih Sebebi Nedir?
Syslog kayıtları kronolojik bir akışa sahiptir. Çift Yönlü Bağlı Liste seçilme nedenleri şunlardır:
* **Çift Yönlü Erişim:** Log kayıtları arasında hem en eskiden en yeniye (baştan sona) hem de en yeni hatayı hızlıca görebilmek için sondan başa doğru verimli bir tarama yapılmasını sağlar.
* **Esnek Veri Yönetimi:** Yeni bir log eklendiğinde dizi kaydırma işlemi gerektirmeden sadece işaretçilerin güncellenmesiyle $O(1)$ karmaşıklığında ekleme yapılabilir.
* **Performans:** Sürekli veri eklenen (append) sistemlerde bellek yönetimini daha efektif kılar.

---

## 💻 Uygulama Detayları

Kod içeriğinde değişken ve fonksiyon isimleri "detaylı açıklama" kriterine uygun olarak amaca yönelik isimlendirilmiştir:

* **`LogNode` (struct):** LogID, zaman damgası, öncelik seviyesi ve mesaj içeriğini taşıyan temel düğüm yapısıdır.
* **`create_new_log`:** `malloc` kullanarak çalışma zamanında yeni bir günlük düğümü için bellek ayırır.
* **`add_log_to_end`:** Yeni oluşturulan log kaydını listenin sonuna güvenli bir şekilde bağlar.
* **`display_logs_forward`:** Bağlı listeyi baştan sona tarayarak standart tablo formatında ekrana basar.
* **`free_list`:** Program sonlanırken kullanılan tüm dinamik belleği `free` ederek bellek sızıntısını (memory leak) önler.

---

## 🚀 Kurulum ve Çalıştırma

1.  **Derleme:**
    ```bash
    gcc main.c -o syslog_app
    ```
2.  **Çalıştırma:**
    ```bash
    ./syslog_app
    ```

---

**Geliştiren:** Göknur Kahraman  
**Bölüm:** Yazılım Mühendisliği (1. Sınıf)  
**Üniversite:** Kırklareli Üniversitesi
