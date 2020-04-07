//复数类
//链接https://acm.sjtu.edu.cn/OnlineJudge/problem/1011

#include <iostream>
#include <iomanip>
using namespace std;

class MyComplex
{
private:
  double x,y;
public:
    MyComplex(){}
    MyComplex(double a,double b)
    {
        x = a;
        y = b;
    }
    MyComplex operator+(MyComplex &another)
    {
        MyComplex a(x+another.x,y+another.y);
        return a;
    }

    MyComplex operator-(MyComplex &another)
    {
        MyComplex a(x-another.x,y-another.y);
        return a;
    }
    MyComplex operator*(MyComplex &another)
    {
        double a=x*another.x-y*another.y,b=x*another.y+y*another.x;
        MyComplex num(a,b);
        return num;
    }
    MyComplex operator/(MyComplex &another)
    {
        double a=(x*(another.x)+y*(another.y))/((another.x)*(another.x)+(another.y)*(another.y));
        double b=(y*(another.x)-x*(another.y))/((another.x)*(another.x)+(another.y)*(another.y));
        MyComplex num(a,b);
        return num;
    }
    MyComplex operator+=(MyComplex &another)
    {
        x = x+another.x;
        y = y+another.y;
        return *this;
    }
    MyComplex operator-=(MyComplex &another)
    {
        x = x-another.x;
        y = y-another.y;
        return *this;
    }
    MyComplex operator*=(MyComplex &another)
    {
        *this = (*this)*another;
        return *this;
    }
    MyComplex operator/=(MyComplex &another)
    {
        *this = (*this)/another;
        return *this;
    }
    friend istream& operator>>(istream &input,MyComplex &num)
    {
        input >> num.x >> num.y;
        return input;
    }
    friend ostream& operator<<(ostream &output,const MyComplex &num)
    {
        output << num.x << ' ' << num.y;
        return output;
    }

};

int main()
{
  MyComplex z1;
  MyComplex z2;

  cin >> z1 >> z2;
  cout.setf(ios::fixed);

  cout << fixed << setprecision(2) << z1 + z2 <<endl;
  cout << fixed << setprecision(2) << z1 - z2 <<endl;
  cout << fixed << setprecision(2) << z1 * z2 <<endl;
  cout << fixed << setprecision(2) << z1 / z2 <<endl;
  cout << fixed << setprecision(2) << (z1 += z2) <<endl;
  cout << fixed << setprecision(2) << (z1 -= z2) <<endl;
  cout << fixed << setprecision(2) << (z1 *= z2) <<endl;
  cout << fixed << setprecision(2) << (z1 /= z2) <<endl;

  return 0;
}
//保留n位小数的两种方法：
//1.cout.setf(ios::fixed);cout << fixed << setprecision(n) << a;
//2.printf("%.nf",s);