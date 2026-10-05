# Dynamic Linking in C using `dlopen()` and `dlsym()`

## 📌 Overview

This project demonstrates **dynamic loading of a shared library in Linux using C**.

The program dynamically loads `libcal.so` at runtime and selects a mathematical function such as:

* `sum()`
* `sub()`
* `mul()`
* `div()`

The function is selected by the user and located dynamically using `dlsym()`.
## 📂 Project Files

Dynamic/
│
├── add.c
├── add.o
├── sub.c
├── sub.o
├── mul.c
├── mul.o
├── div.c
├── div.o
├── calc.h
├── libcal.so
├── main.c
└── maindl
```

### File Description

| File        | Description                                                  |
| ----------- | ------------------------------------------------------------ |
| `main.c`    | Main program that takes user input and selects the operation |
| `calc.h`    | Function declarations                                        |
| `add.c`     | Addition function                                            |
| `sub.c`     | Subtraction function                                         |
| `mul.c`     | Multiplication function                                      |
| `div.c`     | Division function                                            |
| `*.o`       | Object files generated from source files                     |
| `libcal.so` | Shared library containing mathematical functions             |
| `maindl`    | Final executable                                             |

---

## 🔗 Dynamic Linking Concept

In this project, the shared library is **not directly linked with the executable at compile time**.

Instead, the library is loaded during program execution.

```text
        Source Files
     ┌─────┬─────┬─────┬─────┐
     │add.c│sub.c│mul.c│div.c│
     └──┬──┴──┬──┴──┬──┴──┬──┘
        │     │     │     │
        ▼     ▼     ▼     ▼
     add.o  sub.o  mul.o  div.o
        │     │     │     │
        └─────┴─────┴─────┘
                 │
                 ▼
             libcal.so
                 │
                 │ dlopen()
                 ▼
              main.c
                 │
                 │ dlsym()
                 ▼
        Function Pointer
                 │
                 ▼
              Result

## 🛠️ Technologies Used

* C Programming
* Linux
* GCC
* Shared Libraries
* Dynamic Loading
* `dlopen()`
* `dlsym()`
* `dlclose()`
* Function Pointers
## ⚙️ Creating the Object Files

Compile the source files using:

```bash
gcc -c -fPIC add.c sub.c mul.c div.c
```

This generates:

```text
add.o
sub.o
mul.o
div.o
```

The `-fPIC` option generates **Position Independent Code**, which is commonly used when creating shared libraries.

---

## 📦 Creating the Shared Library

Create `libcal.so` using:

```bash
gcc -shared -o libcal.so add.o sub.o mul.o div.o
```

Now the shared library contains:

```text
sum()
sub()
mul()
div()
```

Make sure the function name in `add.c` matches the name used by `dlsym()`.

For example:
c
int sum(int a, int b)
{
    return a + b;
}
## 🔨 Compiling the Main Program

Compile `main.c` with:

```bash
gcc main.c -o maindl -ldl
```

The `-ldl` option links the dynamic loader library required for:

```c
dlopen()
dlsym()
dlclose()
dlerror()
```

---

## ▶️ Running the Program

Run:

```bash
./maindl
```

Example:

```text
Enter two numbers:10 5
1.sum 2.sub 3.mul 4.div
1
Result=15
```

Another example:

```text
Enter two numbers:10 5
1.sum 2.sub 3.mul 4.div
3
Result=50
```

---

## 🧠 How `main.c` Works

The program stores the function names in an array:

```c
char *cal[] = {"sum","sub","mul","div"};
```

If the user selects:

```text
1
```

then:

```c
cal[op-1]
```

becomes:

```c
cal[0]
```

which gives:

```text
"sum"
```

The program then calls:

```c
Dynamic_run("sum", a, b);
```

---

## 🔄 How `dlopen()` Works

```c
handler = dlopen("./libcal.so", RTLD_LAZY);
```

`dlopen()` loads the shared library into memory at runtime.

If loading fails:

```c
if(handler == NULL)
{
    printf("%s\n", dlerror());
    return;
}
```

`dlerror()` displays the error.

---

## 🔍 How `dlsym()` Works

```c
p = (int(*)(int,int))dlsym(handler, str);
```

`dlsym()` searches for the function name inside `libcal.so`.

For example:

```c
dlsym(handler, "sum");
```

returns the address of the `sum()` function.

That address is stored in a function pointer:

```c
int (*p)(int,int);
```

Then the function can be called using:

```c
p(a,b);
```

---

## 🧹 Closing the Shared Library

After the operation is completed:
dlclose(handler);

## 📋 Complete Build Process

The complete sequence is:

```bash
gcc -c -fPIC add.c sub.c mul.c div.c

gcc -shared -o libcal.so add.o sub.o mul.o div.o

gcc main.c -o maindl -ldl

./maindl
```

---

## 🔑 Important Functions

| Function         | Purpose                               |
| ---------------- | ------------------------------------- |
| `dlopen()`       | Loads a shared library                |
| `dlsym()`        | Finds a symbol/function               |
| `dlerror()`      | Reports dynamic loading errors        |
| `dlclose()`      | Closes the shared library             |
| Function pointer | Calls the dynamically loaded function |


## 📚 What I Learned

Through this project, I practiced:

* Shared library creation
* Position Independent Code
* Dynamic library loading
* Function pointers
* Runtime function selection
* `dlopen()` and `dlsym()`
* Linux GCC compilation
* Runtime error handling


Learning **C Programming | Linux | Embedded Systems | Dynamic Linking**
