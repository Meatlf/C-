// tvfm.h -- Tv and Remote classes using a friend member
#ifndef TVFM_H_
#define TVFM_H_

// 前向声明
class Tv; // forward declaration

class Remote
{
public:
    enum State
    {
        Off,
        On
    };
    enum
    {
        MinVal,
        MaxVal = 20
    };
    enum
    {
        Antenna,
        Cable
    };
    enum
    {
        TV,
        DVD
    };

private:
    int mode;

public:
    Remote(int m = TV) : mode(m) {}
    // 只有原型声明，因为此时编译器并不知道Tv类中具体是什么，而不是像tv.h文件中用内联函数实现
    bool volup(Tv &t); // prototype only
    bool voldown(Tv &t);
    void onoff(Tv &t);
    void chanup(Tv &t);
    void chandown(Tv &t);
    void set_mode(Tv &t);
    void set_input(Tv &t);
    void set_chan(Tv &t, int c);
};

class Tv
{
public:
    // 让Remote::set_chan()成为TV类的友元方法
    friend void Remote::set_chan(Tv &t, int c);
    enum State
    {
        Off,
        On
    };
    enum
    {
        MinVal,
        MaxVal = 20
    };
    enum
    {
        Antenna,
        Cable
    };
    enum
    {
        TV,
        DVD
    };

    Tv(int s = Off, int mc = 125) : state(s), volume(5),
                                    maxchannel(mc), channel(2), mode(Cable), input(TV) {}
    void onoff() { state = (state == On) ? Off : On; }
    bool ison() const { return state == On; }
    bool volup();
    bool voldown();
    void chanup();
    void chandown();
    void set_mode() { mode = (mode == Antenna) ? Cable : Antenna; }
    void set_input() { input = (input == TV) ? DVD : TV; }
    void settings() const;

private:
    int state;
    int volume;
    int maxchannel;
    int channel;
    int mode;
    int input;
};

// Remote methods as inline functions
// 此时编译器知道了Tv中具体的内容，所以还是可以将Remote类中的方法设置为内联函数
inline bool Remote::volup(Tv &t) { return t.volup(); }
inline bool Remote::voldown(Tv &t) { return t.voldown(); }
inline void Remote::onoff(Tv &t) { t.onoff(); }
inline void Remote::chanup(Tv &t) { t.chanup(); }
inline void Remote::chandown(Tv &t) { t.chandown(); }
inline void Remote::set_mode(Tv &t) { t.set_mode(); }
inline void Remote::set_input(Tv &t) { t.set_input(); }
inline void Remote::set_chan(Tv &t, int c) { t.channel = c; }
#endif
