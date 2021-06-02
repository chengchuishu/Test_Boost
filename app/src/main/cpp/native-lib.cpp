#include <jni.h>
#include <string>

#include <boost/chrono.hpp>
#include <boost/lexical_cast.hpp>

// when building boost we persisted the NDK version used (BOOST_BUILT_WITH_NDK_VERSION) in this custom header file
#include <boost/version_ndk.hpp>


#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <iostream>

#include <android/log.h>

#define  LOG_TAG    "test===="
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGD(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)


// We are declaring all types as structs only to avoid having to
// type public. If you don't mind doing so, you can just as well
// use class.

// We need to forward-declare the initial state because it can
// only be defined at a point where the state machine is
// defined.
struct Greeting;

// Boost.Statechart makes heavy use of the curiously recurring
// template pattern. The deriving class must always be passed as
// the first parameter to all base class templates.
//
// The state machine must be informed which state it has to
// enter when the machine is initiated. That's why Greeting is
// passed as the second template parameter.
struct Machine : boost::statechart::state_machine< Machine, Greeting > {};

// For each state we need to define which state machine it
// belongs to and where it is located in the statechart. Both is
// specified with Context argument that is passed to
// simple_state<>. For a flat state machine as we have it here,
// the context is always the state machine. Consequently,
// Machine must be passed as the second template parameter to
// Greeting's base (the Context parameter is explained in more
// detail in the next example).
struct Greeting : boost::statechart::simple_state< Greeting, Machine >
{
    // Whenever the state machine enters a state, it creates an
    // object of the corresponding state class. The object is then
    // kept alive as long as the machine remains in the state.
    // Finally, the object is destroyed when the state machine
    // exits the state. Therefore, a state entry action can be
    // defined by adding a constructor and a state exit action can
    // be defined by adding a destructor.
    Greeting()
    {
        std::cout << "Hello World!\n";
        LOGD("Hello World!\n");
    } // entry
    ~Greeting()
    {
        std::cout << "Bye Bye World!\n";
        LOGD("Bye Bye World!\n");
    } // exit
};



extern "C" JNIEXPORT jstring JNICALL
Java_com_yunshen_test_1boost_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string Str = "Hello from C++";

    //-------------------------------------
    /*
    boost::chrono::system_clock::time_point p  = boost::chrono::system_clock::now();
    std::time_t t = boost::chrono::system_clock::to_time_t(p);

    char buffer[26];
    ctime_r(&t, buffer);

    //  std::string tst = std::to_string(3);

    int ver = 72;
    int ver_maj = ver/100000;
    int ver_min = ver / 100 %1000;
    int ver_pat = ver %100;

    std::string Ver_Maj = boost::lexical_cast<std::string>(ver_maj);
    std::string Ver_Min = boost::lexical_cast<std::string>(ver_min);
    std::string Ver_Pat = boost::lexical_cast<std::string>(ver_pat);

    Str += "Boost version: " + Ver_Maj + "." + Ver_Min + "." + Ver_Pat + "\n";

    Str += "built with NDK version: " + std::to_string(21) + "\n";

#if defined(__ANDROID_API__)
    Str += "native Api level: " + std::to_string(__ANDROID_API__) + "\n " ;
#endif

    Str += "\n";
    Str += "Boost chrono says time is \n" + std::string(buffer) + "\n\n";
     */
    //--------------------------------------------


    Machine myMachine;
    // The machine is not yet running after construction. We start
    // it by calling initiate(). This triggers the construction of
    // the initial state Greeting
    myMachine.initiate();
    // When we leave main(), myMachine is destructed what leads to
    // the destruction of all currently active states.


    return env->NewStringUTF(Str.c_str());
}