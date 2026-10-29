#include <iostream>
#include <string>
#include <format>
#include <stdexcept>
using namespace std;

void printLabel(){
    string label = format("{:>8} {:>25} {:>10} {:>12}",
                          "PID", "Name", "CPU (%)", "RAM (MB)");
    
    cout << label << endl;
}

class Process {
private: //це для того, щоб не можна було отримати доступ до обʼєктів поза функціоналом класом
    int pid;
    string name;
    double cpuUsage;
    long memoryUsage;
public:
    Process(int pid = 1, string name = "hello", double cpuUsage = 0.1, long memoryUsage = 1){ //необхідний для простоти задання значень класу, припускаю, що конструктор і деструктор спрацьовують частіше, ніж очікувалось, оскільки обʼєкт ініціалізовується одразу під час додавання у вектор і видаляються як окремі елементи одразу ж після цього
        if(pid > 0 && cpuUsage > 0 && cpuUsage <= 100 && memoryUsage > 0 && !name.empty()){
            this->pid = pid;
            this->name = name;
            this->cpuUsage = cpuUsage;
            this->memoryUsage = memoryUsage;
            
            //cout << "Process started" << endl;
        }else{
            throw invalid_argument("Some information is not correct. Please, start program again with correct values");
        }
        
        
    }

    void printInfo() const {
        string info = format("{:>8d} {:>25} {:>10.2f} {:>12d}\n",
                             pid, name, cpuUsage, memoryUsage);

        cout << info << endl;
    }
    
    int getPID() const{
        return this->pid;
    }
    double getCpuUsage() const{
        return this->cpuUsage;
    }
    long getMemoryUsage()const{
        return this->memoryUsage;
    }
    string getName() const{
        return this->name;
    }
    
    ~Process(){ //викликається зазвичай в кінці класу
        //cout << "Process finished" << endl;
    }
};
/*
 string name - ініціалізація змінних
 const string &name - передача значення як посилання на обʼєкт
 string getName() const; - створення функції у класі, яка передає значення name і гарантує, що воно не буде мінятись
 
 
 Щодо успадкування(inheritance): памʼятаю за існування такої можливості, що успадкований обʼєкт отримує всі поля і функції батьківського(якщо вони у protected/public), але як це реалізовувати не памʼятаю
 */

void printProcesses(const vector<Process> &arr){
    printLabel();
    
    for(int i=0; i <arr.size(); i++){
        arr[i].printInfo();
    }
}


void findProcessByPID(const vector<Process> &arr, const int &pid){
    bool isFound = false;
    for(int i = 0; i<arr.size(); i++){
        if(arr[i].getPID() ==  pid){
            printLabel();
            arr[i].printInfo();
            isFound = true;
            break;
        }
    }
    if(!isFound){
        cout << "Process was not found" << endl;
    }
}

void findMaxProcessorUsage(const vector<Process> &arr){
    int maxUsage = arr[0].getCpuUsage(), maxIndex = 0;
    size_t size = arr.size();
    for(int i = 1; i<size; i++){
        if(arr[i].getCpuUsage() > maxUsage){
            maxUsage = arr[i].getCpuUsage();
            maxIndex = i;
        }
    }
    cout << "Manual loop:" << endl;
    printLabel();
    arr[maxIndex].printInfo();
    
    cout << "STL algorithm:" << endl;
    auto maxElement = max_element(arr.begin(), arr.end(), [](const Process& a, const Process& b) {
            return a.getCpuUsage() < b.getCpuUsage();
        });
    maxElement->printInfo();
}
/*
 Зрозумілішим є mainLoop, але якщо памʼятати ситаксис STL, то він теж цілком зрозумілий
 що таке intent коду не знаю
 складність MainLoop O(n), STL- не знаю, оскільки не вивчав як саме він працює "всередині"
 */

void sortByMemory(vector<Process> &arr){
    sort(arr.begin(), arr.end(), [](const Process& a, const Process& b) {
            return a.getMemoryUsage() > b.getMemoryUsage();
        });
}

void calculateTotalMemory(const vector<Process> &arr){
    int sum = 0;
    
    for(int i = 0; i<arr.size(); i++){
        sum += arr[i].getMemoryUsage();
    }
    
    cout << "Total memory: " << sum << endl;
}

void calculateAverageMemory(const vector<Process> &arr){
    double sum = 0;
    
    for(int i = 0; i<arr.size(); i++){
        sum += arr[i].getMemoryUsage();
    }
    
    double average = sum/arr.size();
    
    string res = format("Average memory: {:.0f}", average);
    
    cout << res << endl;
}

void calculateAverageCPU(const vector<Process> &arr){
    double sum = 0;
    
    for(int i = 0; i<arr.size(); i++){
        sum += arr[i].getCpuUsage();
    }
    
    double average = sum/arr.size();
    
    string res = format("Average CPU: {:.1f}%", average);
    
    cout << res << endl;
}

void calculateMaxProcessor(const vector<Process> &arr){
    auto maxElement = max_element(arr.begin(), arr.end(), [](const Process& a, const Process& b) {
            return a.getCpuUsage() < b.getCpuUsage();
        });
    
    cout << "Max CPU:" << maxElement->getName() << endl;
}

void calculateMaxMemory(const vector<Process> &arr){
    auto maxElement = max_element(arr.begin(), arr.end(), [](const Process& a, const Process& b) {
            return a.getMemoryUsage() < b.getMemoryUsage();
        });
    
    cout << "Max memory: " << maxElement->getName() << endl;
}

void inspectA(Process process);
void inspectB(Process& process);
void inspectC(Process* process);

/*
 копія створюється лише в першому, у другому передається посилання на початковий обʼєкт, а в третьому створюється змінна, яка зберігає адресу оригінала в памʼяті
 оригінальний обʼєкт можна змінювати через другу функцію і третю
 всі три функції не повертають жодного значення, тому null може бути лише в ході виконання функції через те, що не правильно передано параметр чи проведено операції
 не розумію що означає питання: "Як звернутися до member?"
 обʼєкти, які передані до першої і другої функцій живуть стільки, скільки виконується функція, обʼєкт переданий у другу функцію живе стільки, скільки працює програма/область визначення, у якій була ініціалізована
 У першій функції обєктом володія сама функція, у другій функції- область визначення, у якій був ініціалізований process, а у третя функція володіє обʼєктом, який має адресу первинного обʼєкта
 */

int main() {
    /*
    try{
        Process p = Process(-23, "", 346, -345);
    }catch(const invalid_argument& e){
        cerr << "Error: " << e.what() << std::endl;
    }
    */
    
    vector<Process> processes;
    processes.push_back(Process(1236, "chrome.exe", 14.556, 812));
    processes.push_back(Process(1235, "steam.exe", 5.123, 512));
    processes.push_back(Process(1236, "epicGames.exe", 3.658, 435));
    processes.push_back(Process(1237, "minecraft.exe", 20.567, 5678));
    processes.push_back(Process(1238, "photoshop.exe", 15.123, 3455));
    processes.push_back(Process(1239, "davinciResolve.exe", 15.123, 2653));
    processes.push_back(Process(1240, "telegram.exe", 3.543, 678));
    processes.push_back(Process(1241, "viber.exe", 4.234, 543));
    processes.push_back(Process(1242, "youTube.exe", 2.945, 345));
    processes.push_back(Process(1243, "cLion.exe", 10.122, 3455));
    
    while(true){
        Process* tmp = new Process(1243, "cLion.exe", 10.122, 3455);
        delete tmp;
        
        Process* tmp1 = new Process[10];
        delete[] tmp1;
        /*
         ці обʼєкти животь доти, доки не буде їх видалено за допомогою delete
         new "заброньовує" вказану кількість памʼяті в ОЗУ до того, як обʼєкту буде передано необхідну інфу
         здогадуюсь, що створений обʼєкт живе у памʼяті
         у вказівнику зберігається адреса в памʼяті, яка була виділена для цих обʼєктів
         якщо забути delete, то місце у памʼяті не буде вивільнено і згодом при спробі запису у ці комірки буде сміття
         delete p і delete[] p відрізняються тим, що у першому випадку було виділено памʼять для однієї змінної, а в іншому для певної к-сті
         що відбувається із вказівником після видалення не знаю
         аналогічно із dangling pointer
         
         */
        
        string str = "PROCESS STATISTICS";
        int txtLen = str.length();
        
        for(int i = 0; i<30; i++){
            cout << "=";
        }
        cout << endl;
        
        int padding = (30-txtLen)/2;
        cout << string(padding, ' ') << str << endl;
        
        for(int i = 0; i<30; i++){
            cout << "=";
        }
        cout << endl;
        
        cout << "1. Show all processes\n2. Find process by PID\n3. Sort by memory\n4.Show the highest CPU usage\n5. Show statictics\n6. Exit" << endl;
        
        int choise;
        cout << "Enter your choise: ";
        cin >> choise;
        
        switch (choise) {
            case 1:
                printProcesses(processes);
                /*
                 у контексті передачі змінної у функцію, то найкращими є варіанти:
                 vector<Process>& processes- якщо треба змінити початковий обʼєкт
                 const std::vector<Process>& processes - якщо потрібна інформація з початкового масиву
                 */
                break;
            case 2:
                int pidToSearch;
                
                cout << "Enter PID of process that you want to find: ";
                cin >> pidToSearch;
                
                findProcessByPID(processes, pidToSearch);
                break;
            case 3:
                sortByMemory(processes);
                cout << "Sorted vector:\n" << endl;
                printProcesses(processes);
                break;
            case 4:
                cout << "The highest processor usage:\n" << endl;
                findMaxProcessorUsage(processes);
                cout << "\n\n" << endl;
                break;
            case 5:
                cout << "Total processes: " << processes.size() << endl;
                calculateTotalMemory(processes);
                calculateAverageMemory(processes);
                calculateAverageCPU(processes);
                calculateMaxProcessor(processes);
                calculateMaxMemory(processes);
                break;
            case 6:
                return 0;
                break;
                
            default:
                break;
        }
    }
    
    return 0;
}
