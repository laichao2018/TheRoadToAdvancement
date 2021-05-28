#include <iostream>
#include <memory>

// =========================================================================================
//                                      饿   汉   式
//              以空间换时间，因为在类加载的之间就创建了实例，早于线程创建，是线程安全的
// =========================================================================================

class HungryManStyle {
private:
    HungryManStyle() {
        std::cout << "Create a singleton object.\n";
    }

    HungryManStyle(const HungryManStyle &) {

    }

    HungryManStyle &operator=(HungryManStyle &) {

    }

    ~HungryManStyle() {
        std::cout << "Destroy a singleton object.\n";
    }

    static void DestroyInstance(HungryManStyle *);

    // 对于指针或对象的区别，参见博客：
//    https://blog.csdn.net/lvyibin890/article/details/81943637?utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromMachineLearnPai2%7Edefault-3.baidujs&dist_request_id=1328767.1795.16172837965117017&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromMachineLearnPai2%7Edefault-3.baidujs
//    static HungryManStyle instance;
//    static HungryManStyle *instance;
    static std::shared_ptr<HungryManStyle> instance;    // 单例对象，也是类指针

public:
//    static HungryManStyle *getInstance();
//    static void deleteInstance();
    static std::shared_ptr<HungryManStyle> getInstance();
};

// 声明成全局变量，放入静态数据区
//HungryManStyle HungryManStyle::instance;
//
//HungryManStyle *HungryManStyle::getInstance() {
//    return instance;
//}
//
//void HungryManStyle::deleteInstance() {
//    delete instance;
//}

std::shared_ptr<HungryManStyle>HungryManStyle::instance(new HungryManStyle(), HungryManStyle::DestroyInstance);

std::shared_ptr<HungryManStyle> HungryManStyle::getInstance() {
    return instance;
}

void HungryManStyle::DestroyInstance(HungryManStyle *) {
    std::cout << "destroyed object in custom function.\n";
}

// =========================================================================================
//                                      END
// =========================================================================================
