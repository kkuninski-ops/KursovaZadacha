#include <iostream>
#include <string>
using namespace std;

// Ниво 1 - абстрактен базов клас

class InternetService {
protected:// достъпно за този класи неговите наследници
    string provider;
    double monthlyPrice;

public:
    //конструктор по подразбиране, викаме го когато правим обект без начални параметри
    InternetService() : provider("Unknown"), monthlyPrice(0.0) {}
    //инициализиращ констр. викаме го с параметри
    
    InternetService(string prov, double price = 10.0)
        : provider(prov), monthlyPrice(price) {}
    //деструктор да изчистим паметта при del
    virtual ~InternetService() {}
    //вирт. метод абстрактен
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
// наследява internet service(взима неговите атрибути и методи)

class HomeInternet : public InternetService {
protected://да могат дсл и фибер да го ползват
    string address;
    int contractMonths;

public:
//конструктор по подразбиране
    HomeInternet() : InternetService(), address("Unknown"), contractMonths(0) {}
    //months = 12 е default параметър
    HomeInternet(string prov, double price, string addr, int months = 12)
        : InternetService(prov, price), address(addr), contractMonths(months) {}

    void printInfo() override {//override презаписваме вирт метод
        cout << "--- Home Internet ---" << endl;
        cout << "Dostavchik: " << provider << endl;
        cout << "Adres: " << address << endl;
        cout << "Dogovor: " << contractMonths << " meseca" << endl;
        displayPrice();
    }
    //собствен метод връща да/не д
    bool isLongTermContract() {
        return contractMonths >= 12;
    }

    void displayAddress() {
        cout << "Adres na uslugata: " << address << endl;
    }
};

class MobileInternet : public InternetService {
protected://за да може и 5g да го ползва
    string phoneNumber;
    double dataLimitGB;

public:
//конст. по подразбиране
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
    // собствен метод 1
    void checkDataLimit() {
        if (dataLimitGB >= 30) {
            cout << "Golyam paket: " << dataLimitGB << " GB" << endl;
        } else {
            cout << "Osnoveн paket: " << dataLimitGB << " GB" << endl;
        }
    }
    //собствен метод 2
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
//конст. по подразбиране
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
//собствен метод 1
    void displaySpeed() {
        cout << "Skorost - Download: " << downloadSpeed << " Mbps | Upload: " << uploadSpeed << " Mbps" << endl;
    }
//собствен метод 2
    bool isHighSpeed() {
        return downloadSpeed >= 100;
    }
};

class FiveG : public MobileInternet {
protected:// protected за да може FiveGPlus да ги достъпва
    string networkBand;
    int latency;

public:
    //констр. по подразбиране
    FiveG() : MobileInternet(), networkBand("Unknown"), latency(0) {}
    //инициализиращ констр.
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
    //собствен метод 
    void displayLatency() {
        cout << "Zakusnqvane na mrejata: " << latency << " ms" << endl;
    }
    //собствен метод
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
    //констр. по подразбиране
    Fiber() : HomeInternet(), speedMbps(0), isSymmetric(false) {}
    //инициализиращ констр. symmetric = true дефалт параметър
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
// собствен метод 1
    void displayFiberInfo() {
        cout << "Fiber vrazka: " << speedMbps << " Mbps";
        if (isSymmetric) cout << " (simetrichna)" << endl;
        else cout << " (asimetrichna)" << endl;
    }
    //собствен метод 2
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
    //констр. по подразбиране
    FiveGPlus() : FiveG(), maxDevices(0), hasNetworkSlicing(false) {}
    //инициализиращ констр
    //slicing = false defalt параметър
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
    //собствен метод
    void displayDeviceInfo() {
        cout << "Maksimalen broi svurzani ustroistva: " << maxDevices << endl;
    }
    //собствен метод
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
    // масив от обекти на класовете в йерархията
    InternetService* services[6];
    //създаваме обекти динамично с new - заделя памет по време на изпълнение
    services[0] = new HomeInternet("Vivacom", 29.99, "Sofia, ul. Rakovski 15", 24);
    services[1] = new MobileInternet("A1", 19.99, "0888123456", 30.0);
    services[2] = new DSL("Vivacom", 24.99, "Plovdiv, ul. Maritsa 5", 12, 50, 10);
    services[3] = new FiveG("Yetel", 34.99, "0877654321", 50.0, "mmWave", 5);
    services[4] = new Fiber("Bulsatcom", 39.99, "Varna, ul. Primorski 3", 24, 1000, true);
    services[5] = new FiveGPlus("A1", 49.99, "0899111222", 100.0, "Sub-6GHz", 3, 10, true);

    // извикване на printInfo() за всеки обект
    cout << "========== INTERNET SERVICES ==========" << endl << endl;
    for (int i = 0; i < 6; i++) {
        services[i]->printInfo();
        cout << endl;
    }

    // извикване на собствени методи за всеки обект
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
