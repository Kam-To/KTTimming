# KTTimming
An timer that timming by scope, a copycat of llvm::Timer.

## 📖Usage
Simply declare a local varibale of KT::Timer, it would print out the timming result in it's scope when running destructor:

```c++
void HeavyWork() {
    for (int i = 0; i < 999999; i++) {
        __unused int j = rand() % i;
    }
}

int main(int argc, const char * argv[]) {
    KT::Timer MainTimer("Main", "timming cost in main function scope");
    {
        KT::Timer HeavyWorkTimer("Heavywork", "timming cost in closest scope");
        HeavyWork();
    }
    return 0;
}
```
and it would output the user/system/wall time:
```
Name: Heavywork
Des: timming cost in closest scope
UserTime:   0.005935
SystemTime: 0.000024
WallTime:   0.005959

Name: Main
Des: timming cost in main function scope
UserTime:   0.005942
SystemTime: 0.000033
WallTime:   0.005981
```
