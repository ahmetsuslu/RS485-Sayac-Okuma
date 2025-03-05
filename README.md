# RS485 Sayaç Okuma Sistemi

Bu proje, RS485 protokolü üzerinden Makel marka elektrik sayaçlarından veri okuyup SD karta kaydeden bir Arduino uygulamasıdır.

## Proje Özeti

Bu sistem, iki farklı elektrik sayacından (seri numaraları: 52******41 ve 52******91) düzenli aralıklarla veri okur ve bu verileri CSV formatında SD karta kaydeder. Sayaçlardan tarih, saat ve tüketim değerleri alınır.

> Not: Güvenlik nedeniyle sayaç numaraları maskelenmiştir. Format: İlk iki rakam + yıldız + son iki rakam şeklindedir.

## Proje Hakkında

Bu sayaç okuma sistemi, Isparta Uygulamalı Bilimler Üniversitesi, Ziraat Fakültesi, Tarım Makineleri ve Teknolojileri Mühendisliği Bölümü Öğretim Üyesi Prof. Dr. Ahmet Kamil BAYHAN hocamın isteği üzerine tarafımca geliştirilmiştir.

## Donanım Gereksinimleri

- Arduino (Uno, Mega veya benzeri)
- RS485 haberleşme modülü
- SD kart modülü
- Makel marka elektrik sayaçları (veya uyumlu RS485 protokolünü destekleyen sayaçlar)
- LED'ler veya durum göstergeleri için bileşenler
- Güç kaynağı

## Bağlantı Şeması

```
Arduino Pin 4  -> SD Kart CS (Chip Select)
Arduino Pin 9  -> RS485 Modülü RTS (Request to Send)
Arduino Pin 6  -> Durum LED 1
Arduino Pin 7  -> Durum LED 2
Arduino TX/RX -> RS485 Modülü TX/RX
```

## Yazılım Özellikleri

- RS485 protokolü üzerinden sayaçlarla iletişim
- Sayaçlardan tarih, saat ve tüketim verilerinin okunması
- Verilerin CSV formatında SD karta kaydedilmesi
- Durum göstergeleri ile sistem durumunun izlenmesi

## Kurulum

1. Arduino IDE'yi açın
2. Gerekli kütüphaneleri yükleyin: SPI ve SD
3. `sayac_okuma_makel.ino` dosyasını Arduino IDE'de açın
4. Arduino kartınızı seçin ve kodu yükleyin
5. Donanım bağlantılarını yapın
6. Sistemi çalıştırın

## Kullanım

Sistem çalıştırıldığında:
1. İlk olarak SD kart bağlantısı kontrol edilir
2. Başarılı bağlantı durumunda, sistem iki sayaçtan sırayla veri okumaya başlar
3. Okunan veriler "sayaclar.csv" dosyasına kaydedilir
4. LED göstergeleri sistem durumunu belirtir:
   - Pin 6 HIGH: SD kart hatası
   - Pin 7 HIGH/LOW: Veri okuma/yazma işlemi durumu

## Veri Formatı

SD kartta oluşturulan CSV dosyası aşağıdaki formatta veri içerir:

```
Tarih, Saat, Soldaki Sayaç(52******41), Tarih, Saat, Sağdaki Sayaç(52******91)
```

## Sorun Giderme

- SD kart bağlantı hatası: Pin 6 LED'i sürekli yanıyorsa SD kart bağlantısını kontrol edin
- Sayaç iletişim hatası: Kablo bağlantılarını ve RS485 modülünün doğru çalıştığını kontrol edin
- Veri kayıt hatası: SD kartın doğru formatlandığını ve yazma korumalı olmadığını kontrol edin

## Lisans

Bu proje açık kaynak olarak MIT lisansı altında dağıtılmaktadır.

## Katkıda Bulunanlar

- Ahmet Süslü - İlk geliştirici

## İletişim

Sorularınız veya önerileriniz için mail@ahmetsuslu.com adresine e-posta gönderebilirsiniz. 