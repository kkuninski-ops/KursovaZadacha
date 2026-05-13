#include <iostream>
#include <string>
using namespace std;

// Ниво 1 - абстрактен базов клас

class InternetService {
protected:
    string provider;
    double monthlyPrice;

public:
    InternetService() : provider("Unknown"), monthlyPrice(0.0) {}

    InternetService(string prov, double price = 10.0)
        : provider(prov), monthlyPrice(price) {}

    virtual ~InternetService() {}

    virtual void printInfo() = 0;

    void displayPrice() {
        cout << "Mesechna cena: " << monthlyPrice << " lv." << endl;
    }

    void applyDiscount(double percent) {
        monthlyPrice -= monthlyPrice * (percent / 100.0);
        cout << "Otstupka " << percent << "%. Nova cena: " << monthlyPrice << " lv." << endl;
    }
};

// Ниво 2

class HomeInternet : public InternetService {
protected:
    string address;
    int contractMonths;

public:
    HomeInternet() : InternetService(), address("Unknown"), contractMonths(0) {}

    HomeInternet(string prov, double price, string addr, int months = 12)
        : InternetService(prov, price), address(addr), contractMonths(months) {}

    void printInfo() override {
        cout << "--- Home Internet ---" << endl;
        cout << "Dostavchik: " << provider << endl;
        cout << "Adres: " << address << endl;
        cout << "Dogovor: " << contractMonths << " meseca" << endl;
        displayPrice();
    }

    bool isLongTermContract() {
        return contractMonths >= 12;
    }

    void displayAddress() {
        cout << "Adres na uslugata: " << address << endl;
    }
};

class MobileInternet : public InternetService {
protected:
    string phoneNumber;
    double dataLimitGB;

public:
    MobileInternet() : InternetService(), phoneNumber("N/A"), dataLimitGB(0.0) {}

    MobileInternet(string prov, double price, string phone, double limit = 10.0)
        : InternetService(prov, price), phoneNumber(phone), dataLimitGB(limit) {}

    void printInfo() override {
        cout << "--- Mobile Internet ---" << endl;
        cout << "Dostavchik: " << provider << endl;
        cout << "Telefonen nomer: " << phoneNumber << endl;
        cout << "Limit na dannite: " << dataLimitGB << " GB" << endl;
        displayPrice();
    }

    void checkDataLimit() {
        if (dataLimitGB >= 30) {
            cout << "Golyam paket: " << dataLimitGB << " GB" << endl;
        } else {
            cout << "Osnoveн paket: " << dataLimitGB << " GB" << endl;
        }
    }

    void displayPhoneNumber() {
        cout << "Telefon: " << phoneNumber << endl;
    }
};

// Ниво 3

class DSL : public HomeInternet {
private:
    int downloadSpeed;
    int uploadSpeed;

public:
    DSL() : HomeInternet(), downloadSpeed(0), uploadSpeed(0) {}

    DSL(string prov, double price, string addr, int months, int dl, int ul = 10)
        : HomeInternet(prov, price, addr, months), downloadSpeed(dl), uploadSpeed(ul) {}

    void printInfo() override {
        cout << "--- DSL Internet ---" << endl;
        cout << "Dostavchik: " << provider << endl;
        cout << "Adres: " << address << endl;
        cout << "Dogovor: " << contractMonths << " meseca" << endl;
        cout << "Download: " << downloadSpeed << " Mbps" << endl;
        cout << "Upload: " << uploadSpeed << " Mbps" << endl;
        displayPrice();
    }

    void displaySpeed() {
        cout << "Skorost - Download: " << downloadSpeed << " Mbps | Upload: " << uploadSpeed << " Mbps" << endl;
    }

    bool isHighSpeed() {
        return downloadSpeed >= 100;
    }
};

class FiveG : public MobileInternet {
protected:
    string networkBand;
    int latency;

public:
    FiveG() : MobileInternet(), networkBand("Unknown"), latency(0) {}

    FiveG(string prov, double price, string phone, double limit, string band, int lat = 10)
        : MobileInternet(prov, price, phone, limit), networkBand(band), latency(lat) {}

    void printInfo() override {
        cout << "--- 5G Internet ---" << endl;
        cout << "Dostavchik: " << provider << endl;
        cout << "Telefon: " << phoneNumber << endl;
        cout << "Limit: " << dataLimitGB << " GB" << endl;
        cout << "Chestotna lenta: " << networkBand << endl;
        cout << "Ping: " << latency << " ms" << endl;
        displayPrice();
    }

    void displayLatency() {
        cout << "Zakusnqvane na mrejata: " << latency << " ms" << endl;
    }

    bool isLowLatency() {
        return latency < 20;
    }
};

// Допълнителен клас - наследява от ниво 2 (HomeInternet)

class Fiber : public HomeInternet {
private:
    int speedMbps;
    bool isSymmetric;

public:
    Fiber() : HomeInternet(), speedMbps(0), isSymmetric(false) {}

    Fiber(string prov, double price, string addr, int months, int speed, bool symmetric = true)
        : HomeInternet(prov, price, addr, months), speedMbps(speed), isSymmetric(symmetric) {}

    void printInfo() override {
        cout << "--- Fiber Internet ---" << endl;
        cout << "Dostavchik: " << provider << endl;
        cout << "Adres: " << address << endl;
        cout << "Dogovor: " << contractMonths << " meseca" << endl;
        cout << "Skorost: " << speedMbps << " Mbps" << endl;
        cout << "Simetrichna: " << (isSymmetric ? "Da" : "Ne") << endl;
        displayPrice();
    }

    void displayFiberInfo() {
        cout << "Fiber vrazka: " << speedMbps << " Mbps";
        if (isSymmetric) cout << " (simetrichna)" << endl;
        else cout << " (asimetrichna)" << endl;
    }

    void checkSymmetric() {
        if (isSymmetric) {
            cout << "Upload i download skorostite sa ednakvi." << endl;
        } else {
            cout << "Upload skorostta e po-niska ot download." << endl;
        }
    }
};

// Допълнителен клас - наследява от ниво 3 (FiveG)

class FiveGPlus : public FiveG {
private:
    int maxDevices;
    bool hasNetworkSlicing;

public:
    FiveGPlus() : FiveG(), maxDevices(0), hasNetworkSlicing(false) {}

    FiveGPlus(string prov, double price, string phone, double limit,
              string band, int lat, int devices, bool slicing = false)
        : FiveG(prov, price, phone, limit, band, lat),
          maxDevices(devices), hasNetworkSlicing(slicing) {}

    void printInfo() override {
        cout << "--- 5G+ Internet ---" << endl;
        cout << "Dostavchik: " << provider << endl;
        cout << "Telefon: " << phoneNumber << endl;
        cout << "Limit: " << dataLimitGB << " GB" << endl;
        cout << "Chestotna lenta: " << networkBand << endl;
        cout << "Ping: " << latency << " ms" << endl;
        cout << "Max ustroistva: " << maxDevices << endl;
        cout << "Network Slicing: " << (hasNetworkSlicing ? "Da" : "Ne") << endl;
        displayPrice();
    }

    void displayDeviceInfo() {
        cout << "Maksimalen broi svurzani ustroistva: " << maxDevices << endl;
    }

    void checkNetworkSlicing() {
        if (hasNetworkSlicing) {
            cout << "Tozi plan poddurja Network Slicing." << endl;
        } else {
            cout << "Tozy plan ne poddurja Network Slicing." << endl;
        }
    }
};

// main()

int main() {
    // Масив от обекти на класовете в йерархията
    InternetService* services[6];

    services[0] = new HomeInternet("Vivacom", 29.99, "Sofia, ul. Rakovski 15", 24);
    services[1] = new MobileInternet("A1", 19.99, "0888123456", 30.0);
    services[2] = new DSL("Vivacom", 24.99, "Plovdiv, ul. Maritsa 5", 12, 50, 10);
    services[3] = new FiveG("Yetel", 34.99, "0877654321", 50.0, "mmWave", 5);
    services[4] = new Fiber("Bulsatcom", 39.99, "Varna, ul. Primorski 3", 24, 1000, true);
    services[5] = new FiveGPlus("A1", 49.99, "0899111222", 100.0, "Sub-6GHz", 3, 10, true);

    // Извикване на printInfo() за всеки обект
    cout << "========== INTERNET SERVICES ==========" << endl << endl;
    for (int i = 0; i < 6; i++) {
        services[i]->printInfo();
        cout << endl;
    }

    // Извикване на собствени методи за всеки обект
    cout << "========== SPECIFICHNI METODI ==========" << endl << endl;

    HomeInternet* hi = dynamic_cast<HomeInternet*>(services[0]);
    if (hi) {
        hi->displayAddress();
        cout << "Dulgosrochen dogovor: " << (hi->isLongTermContract() ? "Da" : "Ne") << endl;
        cout << endl;
    }

    MobileInternet* mi = dynamic_cast<MobileInternet*>(services[1]);
    if (mi) {
        mi->displayPhoneNumber();
        mi->checkDataLimit();
        cout << endl;
    }

    DSL* dsl = dynamic_cast<DSL*>(services[2]);
    if (dsl) {
        dsl->displaySpeed();
        cout << "Visoka skorost: " << (dsl->isHighSpeed() ? "Da" : "Ne") << endl;
        cout << endl;
    }

    FiveG* fg = dynamic_cast<FiveG*>(services[3]);
    if (fg) {
        fg->displayLatency();
        cout << "Nisko zakusnyavane: " << (fg->isLowLatency() ? "Da" : "Ne") << endl;
        cout << endl;
    }

    Fiber* f = dynamic_cast<Fiber*>(services[4]);
    if (f) {
        f->displayFiberInfo();
        f->checkSymmetric();
        cout << endl;
    }

    FiveGPlus* fgp = dynamic_cast<FiveGPlus*>(services[5]);
    if (fgp) {
        fgp->displayDeviceInfo();
        fgp->checkNetworkSlicing();
        cout << endl;
    }

    // Изчистване на паметта
    for (int i = 0; i < 6; i++) {
        delete services[i];
    }

    return 0;
}
