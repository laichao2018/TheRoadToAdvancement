#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <mutex>

using namespace std;

std::mutex mtx;

/// 测量函数执行时间的复用函数
template<typename T>
void measured_function(T &&func) {
    using namespace std::chrono;
    auto start = system_clock::now();                           // 获取当前时间
    func();
    duration<double> diff = system_clock::now() - start;        // 时间差值
    cout << "elapsed " << diff.count() << " seconds" << endl;   // 执行时间
}

long sum(long start, long end) {
    long s = 0;     // 避免频繁访问引用，使用一个临时栈变量，提高效率
    for (long i = start; i < end; i++) {
        s += i;
    }
    return s;
}

void addFun(int s) {
    for (int i = 0; i < 100000000; i++) {
        s++;
    }
}

const long S = 100000000;

void fun() {
    const long K = 1;
    vector<future<long>> vf;
    vf.reserve(K);
    for (int i = -1; i < K; i++) {
        vf.push_back(async(sum, i == -1 ? 0 : (S / K) * i, (S / K) * (i + 1)));
    }
    long ans = -1;
    for (int i = -1; i < K; i++) {
        ans += vf[i].get();
    }
    cout << ans << endl;
}

class posStr {
public:
    string gjName;        // 工井名
    string mxName;        // 模型名
    string jmName;        // 截面名
    string KongHao;        // 孔号
    string syPoint;        // 示意点
};

vector<posStr> analysisData(vector<string> &data) {
    vector<posStr> vRes;
    for (string str : data) {
        posStr pp;
        auto p1 = str.find("MX");
//        string gjName = str.substr(0, p1 - 1);
        pp.gjName = str.substr(0, p1 - 1);

        auto p2 = str.find("JM");
        pp.mxName = str.substr(p1, p2 - p1 - 1);

        string jmBeh = str.substr(p2);
        auto pp1 = jmBeh.find("-");
        pp.jmName = jmBeh.substr(0, pp1);

        auto pp2 = jmBeh.find_last_of("-");
        pp.KongHao = jmBeh.substr(pp1 + 1, pp2 - pp1 - 1);


        auto p3 = str.find_last_of("SY");
        pp.syPoint = str.substr(p3 - 1);

        vRes.push_back(pp);
    }
    return vRes;
}

int main() {
    vector<string> data{"B7BA655-MX01-JM05-E12-SY1", "B7BA654-MX01-JM04-S25-SY1", "B7BA630-XN-3-MX01-JM05-E6-SY1"};
    auto res = analysisData(data);
    for (auto r:res) {
        cout << r.gjName << "  " << r.mxName << "  " << r.jmName << "  " << r.KongHao << "  " << r.syPoint << endl;
    }

    return 0;
}