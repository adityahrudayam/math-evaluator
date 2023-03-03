/*
    Author/Creator:-
    Kaushik Chaturvedula
    Github username: adityahrudayam
*/

#include <iostream>
#include "ExpressionEvaluator.hpp"
#include "EvaluateExpressionD.hpp"
#include "EvaluateExpressionI.hpp"
#include "MatrixOperator.hpp"

using namespace std::string_literals;

using std::cout;
using std::endl;

int main(int argc, const char *argv[])
{
    // LoadLDMFromFile("./matrices.txt", 0LL);
    string temp[6] = {"1", "2", "3", "4", "5", "6"};
    MatrixLD mat('\02', '\03', temp);
    cout << mat << endl;
    takeInputAndEval();

    // cout << evaluateExpression("1    + 2  - 0.008"s) << endl;    // 2.992
    cout << evaluateExpression(" 2-1 + 2 "s) << endl;            // 3
    cout << evaluateExpression("(1+(4+5+2)-3)+(6+8)"s) << endl;  // 23
    cout << evaluateExpression("- 2"s) << endl;                  // -2
    cout << evaluateExpression("- (2) - (-3+4 - (6))"s) << endl; // 3
    cout << evaluateExpression("1"s) << endl;                    // 1
    cout << evaluateExpression("1/3*9"s) << endl;                // 0
    cout << evaluateExpression("9*1/3"s) << endl;                // 3
    cout << evaluateExpression("1-(     -2)"s) << endl;          // 3
    cout << evaluateExpression("1-(     -2)^3"s) << endl;        // 1-(-8)=9
    cout << evaluateExpression("1*5     -2^3"s) << endl;         // 5-8=-3
    cout << evaluateExpression("1*5-(     -2)^3"s) << endl;      // 5-(-8)=13
    cout << evaluateExpression("1/44-(     -2)^5"s) << endl;     // 32
    cout << evaluateExpression("1-(     -2)^6"s) << endl;        // 1-64=-63
    cout << evaluateExpression("1-(     -2)^3"s) << endl;        // 1-(-8)=9
    cout << evaluateExpression("1-(     -2)^3^2"s) << endl;      // 1-(-2)^9=1-(-512)=513
    cout << evaluateExpression("1-(     -2)^3^2^2"s) << endl;    // 1-(-2)^(3^4)
    cout << evaluateExpression("1-(     -2)^2^2^2"s) << endl;    // 1-(-2)^16 = 1-65536=-65535
    cout << evaluateExpression("-1+(     -2)^3"s) << endl;       // -1+(-8)=-9
    cout << evaluateExpression("(3-(5-(8)-(2+(9-(0-(8-(2))))-(4))-(4)))"s) << endl;
    cout << evaluateExpression("-(3-(5-(8)-(2+(9-(0-(8-(2))))-(4))-(4)))"s) << endl;
    cout << evaluateExpression("-(3*(5-(-8)-(-2+(9-(0-(8/(-2))))-(4)))+(-4))"s) << endl;
    cout << evaluateExpression("-(3*(5-(-8)-(-2+(9-(0-(8/(-2))))-(4)))+(-4)^2)"s) << endl;
    cout << evaluateExpression("-(3*(5-(-8)^2-(-2+(9-(0-(8/(-2))))-(4)))+(-4)^2)"s) << endl;
    cout << evaluateExpression("-(3*(5-(-8)-(-2+(9-(0-(8/(-2))))-(4))+(-4)))"s) << endl;
    cout << evaluateExpression("-(3*(5-(-8)-(-2+(9-(0-(8/(-2))))-(4))+(-4)))^2"s) << endl;
    cout << evaluateExpression("-(3*(5-(-8)-(-2+(9-(0-(8/(-2))))-(4))+(-4)))^3"s) << endl;
    cout << evaluateExpression("(-(3*(5-(-8)-(-2+(9-(0-(8/(-2))))-(4))+(-4))))^2"s) << endl;
    cout << evaluateExpression("(-(3*(5-(-8)-(-2+(9-(0-(8/(-2))))-(4))+(-4))))%7^2"s) << endl;
    cout << evaluateExpression("(-(3*(5-(-8)-(-2+(9-(0-(8/(-2))))-(4))+(-4))))^2%7"s) << endl;
    cout << "############ part-2 ###############" << endl;
    cout << evaluateExpression("1-2-3") << endl;        //-4
    cout << evaluateExpression("1-2^-3") << endl;       // 1-1/8=0.875
    cout << evaluateExpression("1-(-2)^3") << endl;     // 1-(-8)=9
    cout << evaluateExpression("1-(-2)^-3") << endl;    // 1-(-1/8)=1.125
    cout << evaluateExpression("1-(-2)^-3^-2") << endl; // 1-(-2)^(1/9) gives a complex no.
    cout << evaluateExpression("1-(-2)^-3^2") << endl;  // 1-(-2)^9=1-(-512)=1+512=513
    cout << evaluateExpression("1-(-2)^0.5") << endl;   // sqrt(-2) is a complex no.
    cout << evaluateExpression("1-(-2)^-2") << endl;    // 1-1/4=0.75
    cout << "-------------Function tests--------------" << endl;
    cout << evaluateExpression("sin(30)*2") << endl;       // 1/2*2=1
    cout << evaluateExpression("-sin(30*1)") << endl;      // -0.5
    cout << evaluateExpression("sin(30)") << endl;         // 0.5
    cout << evaluateExpression("cos(sin(30))") << endl;    // cos0.5deg
    cout << evaluateExpression("tan(sin(30))") << endl;    // tan0.5
    cout << evaluateExpression("sin(30)/cos(30)") << endl; // =tan30=
    cout << evaluateExpression("sin(30^2)") << endl;
    cout << evaluateExpression("sin(30+3)-(-3*cos(50))") << endl;
    cout << evaluateExpression("cos(sin(30))") << endl;    // cos0.5deg <= 1
    cout << evaluateExpression("cos(sin(30)+30)") << endl; // cos30.5deg >= sqrt(3)/2
    cout << "-------------Important tests--------------" << endl;
    cout << evaluateExpression("-(+8 .8 8)+(9)-3 +(2^-5) -(-(+10))-loge(778.887 77)") << endl; // 0.493383
    cout << evaluateExpression("-(+8 .8 8) -loge(778.887 77)") << endl;                        // -15.5379
    cout << evaluateExpression("3^ log(4, 4)"s) << endl;                                       // 3
    cout << evaluateExpression("log 2(3 ^ log(4,4))"s) << endl;                                // ~1.58
    cout << evaluateExpression("log2(8)"s) << endl;                                            // 3
    cout << evaluateExpression("log2(6)"s) << endl;                                            // 2.584
    cout << evaluateExpression("log2(3^log(4,4)+log2(8))"s) << endl;                           // 2.584
    cout << evaluateExpression("log2(3^log(4,4)+log2(8))^0.8"s) << endl;                       // 2.13
    cout << evaluateExpression("log2(2)"s) << endl;                                            // 1
    cout << evaluateExpression("log2(3^log(4,4)+log2(8))^0.8+log2(2)"s) << endl;               // 3.13

    cout << evaluateExpression("log2(3^log2(4)+log2(8))^0.8+log2(2)") << endl;                                  // 3.77
    cout << evaluateExpression("log2(2^log(loge(555),4)+log2(8))^0.8+log2(2)"s) << endl;                        // 3.05673
    cout << evaluateExpression("-2^-2^1+log2(2^-4*4)^1^log2(2^log(loge(555),4)+log2(8))^0.8+log2(2)"s) << endl; // -0.75
    cout << evaluateExpression("-2^-2^1+log2(2^-4*4)^1^log2(2^log(4,4)+log2(8))^0.8+log2(2)"s) << endl;         // -0.75

    cout << "--------------------------------------------" << endl;

    cout << evaluateExpressionD("1    + 2  - 0.008"s) << endl;
    cout << evaluateExpressionD(" 2-1 + 2 "s) << endl;
    cout << evaluateExpressionD("(1+(4+5+2)-3)+(6+8)"s) << endl;
    cout << evaluateExpressionD("- 2"s) << endl;
    cout << evaluateExpressionD("- (2) - (-3+4 - (6))"s) << endl;
    cout << evaluateExpressionD("1"s) << endl;
    cout << evaluateExpressionD("1/3*9"s) << endl;             // 0
    cout << evaluateExpressionD("9*1/3"s) << endl;             // 3
    cout << evaluateExpressionD("1-(     -2)"s) << endl;       // 3
    cout << evaluateExpressionD("1-(     -2)^3"s) << endl;     // 1-(-8)=9
    cout << evaluateExpressionD("1*5     -2^3"s) << endl;      // 5-8=-3
    cout << evaluateExpressionD("1*5-(     -2)^3"s) << endl;   // 5-(-8)=13
    cout << evaluateExpressionD("1/44-(     -2)^5"s) << endl;  // 32
    cout << evaluateExpressionD("1-(     -2)^6"s) << endl;     // 1-64=-63
    cout << evaluateExpressionD("1-(     -2)^3"s) << endl;     // 1-(-8)=9
    cout << evaluateExpressionD("1-(     -2)^3^2"s) << endl;   // 1-(-2)^9=1-(-512)=513
    cout << evaluateExpressionD("1-(     -2)^3^2^2"s) << endl; // 1-(-2)^(3^4) - out of bounds
    cout << evaluateExpressionD("1-(     -2)^2^2^2"s) << endl; // 1-(-2)^16 = 1-65536=-65535
    cout << evaluateExpressionD("-1+(     -2)^3"s) << endl;    // -1+(-8)=-9
    cout << evaluateExpressionD("(3-(5-(8)-(2+(9-(0-(8-(2))))-(4))-(4)))"s) << endl;
    cout << evaluateExpressionD("-(3-(5-(8)-(2+(9-(0-(8-(2))))-(4))-(4)))"s) << endl;
    cout << evaluateExpressionD("-(3*(5-(-8)-(-2+(9-(0-(8/(-2))))-(4)))+(-4))"s) << endl;
    cout << evaluateExpressionD("-(3*(5-(-8)-(-2+(9-(0-(8/(-2))))-(4)))+(-4)^2)"s) << endl;
    cout << evaluateExpressionD("-(3*(5-(-8)^2-(-2+(9-(0-(8/(-2))))-(4)))+(-4)^2)"s) << endl;
    cout << evaluateExpressionD("-(3*(5-(-8)-(-2+(9-(0-(8/(-2))))-(4))+(-4)))"s) << endl;
    cout << evaluateExpressionD("-(3*(5-(-8)-(-2+(9-(0-(8/(-2))))-(4))+(-4)))^2"s) << endl;
    cout << evaluateExpressionD("-(3*(5-(-8)-(-2+(9-(0-(8/(-2))))-(4))+(-4)))^3"s) << endl;
    cout << evaluateExpressionD("(-(3*(5-(-8)-(-2+(9-(0-(8/(-2))))-(4))+(-4))))^2"s) << endl;
    cout << "############ part-2 ###############" << endl;
    cout << evaluateExpressionD("1-2-3") << endl;        //-4
    cout << evaluateExpressionD("1-2^-3") << endl;       // 1-1/8=0.875
    cout << evaluateExpressionD("1-(-2)^3") << endl;     // 1-(-8)=9
    cout << evaluateExpressionD("1-(-2)^-3") << endl;    // 1-(-1/8)=1.125
    cout << evaluateExpressionD("1-(-2)^-3^-2") << endl; // 1-(-2)^(1/9) gives a complex no.
    cout << evaluateExpressionD("1-(-2)^-3^2") << endl;  // 1-(-2)^9=1-(-512)=1+512=513
    cout << evaluateExpressionD("1-(-2)^0.5") << endl;   // sqrt(-2) is a complex no.
    cout << evaluateExpressionD("1-(-2)^-2") << endl;    // 1-1/4=0.75
    cout << "-------------Function tests--------------" << endl;
    cout << evaluateExpressionD("sin(30)*2") << endl;       // 1/2*2=1
    cout << evaluateExpressionD("-sin(30*1)") << endl;      // -0.5
    cout << evaluateExpressionD("sin(30)") << endl;         // 0.5
    cout << evaluateExpressionD("cos(sin(30))") << endl;    // cos0.5deg
    cout << evaluateExpressionD("tan(sin(30))") << endl;    // tan0.5
    cout << evaluateExpressionD("sin(30)/cos(30)") << endl; // =tan30=
    cout << evaluateExpressionD("sin(30^2)") << endl;
    cout << evaluateExpressionD("sin(30+3)-(-3*cos(50))") << endl;
    cout << evaluateExpressionD("cos(sin(30))") << endl;    // cos0.5deg <= 1
    cout << evaluateExpressionD("cos(sin(30)+30)") << endl; // cos30.5deg >= sqrt(3)/2
    cout << "-------------Important tests--------------" << endl;
    cout << evaluateExpressionD("-(+8 .8 8)+(9)-3 +(2^-5) -(-(+10))-loge(778.887 77)") << endl; // 0.493383
    cout << evaluateExpressionD("-(+8 .8 8) -loge(778.887 77)") << endl;                        // -15.5379
    cout << evaluateExpressionD("3^ log(4, 4)"s) << endl;                                       // 3
    cout << evaluateExpressionD("log 2(3 ^ log(4,4))"s) << endl;                                // ~1.58
    cout << evaluateExpressionD("log2(8)"s) << endl;                                            // 3
    cout << evaluateExpressionD("log2(6)"s) << endl;                                            // 2.584
    cout << evaluateExpressionD("log2(3^log(4,4)+log2(8))"s) << endl;                           // 2.584
    cout << evaluateExpressionD("log2(3^log(4,4)+log2(8))^0.8"s) << endl;                       // 2.13
    cout << evaluateExpressionD("log2(2)"s) << endl;                                            // 1
    cout << evaluateExpressionD("log2(3^log(4,4)+log2(8))^0.8+log2(2)"s) << endl;               // 3.13

    cout << evaluateExpressionD("log2(3^log2(4)+log2(8))^0.8+log2(2)") << endl;                                      // 3.77
    cout << evaluateExpressionD("log2(2^log(loge(555),4)+log2(8))^0.8+log2(2)"s) << endl;                            // 3.05673
    cout << evaluateExpressionD("-2^-2^1+log2(2^-4*4)^1^log2(2^log(loge(555),4)+log2(8))^0.8+log2(2)"s) << endl;     // -0.75
    cout << evaluateExpressionD("-2^-2^1+log2(2^-4*4)^1^log2(2^log(4,4)+log2(8))^0.8+log2(2)"s) << endl;             // -0.75
    cout << evaluateExpressionD("-02^-002^1+log2(2^-004*4)^1^log2(002^log(4,4)+log2(8))^000.08+log2(002)"s) << endl; // -0.75
    cout << "--------------------------------------------" << endl;

    cout << evaluateExpressionI("1    + 2  - 0.008"s) << endl;
    cout << evaluateExpressionI(" 2-1 + 2 "s) << endl;
    cout << evaluateExpressionI("(1+(4+5+2)-3)+(6+8)"s) << endl;
    cout << evaluateExpressionI("- 2"s) << endl;
    cout << evaluateExpressionI("- (2) - (-3+4 - (6))"s) << endl;
    cout << evaluateExpressionI("1"s) << endl;
    cout << evaluateExpressionI("1/3*9"s) << endl;             // 0
    cout << evaluateExpressionI("9*1/3"s) << endl;             // 3
    cout << evaluateExpressionI("1-(     -2)"s) << endl;       // 3
    cout << evaluateExpressionI("1-(     -2)^3"s) << endl;     // 1-(-8)=9
    cout << evaluateExpressionI("1*5     -2^3"s) << endl;      // 5-8=-3
    cout << evaluateExpressionI("1*5-(     -2)^3"s) << endl;   // 5-(-8)=13
    cout << evaluateExpressionI("1/44-(     -2)^5"s) << endl;  // 32
    cout << evaluateExpressionI("1-(     -2)^6"s) << endl;     // 1-64=-63
    cout << evaluateExpressionI("1-(     -2)^3"s) << endl;     // 1-(-8)=9
    cout << evaluateExpressionI("1-(     -2)^3^2"s) << endl;   // 1-(-2)^9=1-(-512)=513
    cout << evaluateExpressionI("1-(     -2)^3^2^2"s) << endl; // 1-(-2)^(3^4) - out of bounds
    cout << evaluateExpressionI("1-(     -2)^2^2^2"s) << endl; // 1-(-2)^16 = 1-65536=-65535
    cout << evaluateExpressionI("-1+(     -2)^3"s) << endl;    // -1+(-8)=-9
    cout << evaluateExpressionI("(3-(5-(8)-(2+(9-(0-(8-(2))))-(4))-(4)))"s) << endl;
    cout << evaluateExpressionI("-(3-(5-(8)-(2+(9-(0-(8-(2))))-(4))-(4)))"s) << endl;
    cout << evaluateExpressionI("-(3*(5-(-8)-(-2+(9-(0-(8/(-2))))-(4)))+(-4))"s) << endl;
    cout << evaluateExpressionI("-(3*(5-(-8)-(-2+(9-(0-(8/(-2))))-(4)))+(-4)^2)"s) << endl;
    cout << evaluateExpressionI("-(3*(5-(-8)^2-(-2+(9-(0-(8/(-2))))-(4)))+(-4)^2)"s) << endl;
    cout << evaluateExpressionI("-(3*(5-(-8)-(-2+(9-(0-(8/(-2))))-(4))+(-4)))"s) << endl;
    cout << evaluateExpressionI("-(3*(5-(-8)-(-2+(9-(0-(8/(-2))))-(4))+(-4)))^2"s) << endl;
    cout << evaluateExpressionI("-(3*(5-(-8)-(-2+(9-(0-(8/(-2))))-(4))+(-4)))^3"s) << endl;
    cout << evaluateExpressionI("(-(3*(5-(-8)-(-2+(9-(0-(8/(-2))))-(4))+(-4))))^2"s) << endl;
    cout << "############ part-2 ###############" << endl;
    cout << evaluateExpressionI("1-2-3") << endl;        //-4
    cout << evaluateExpressionI("1-2^-3") << endl;       // 1-1/8=0.875
    cout << evaluateExpressionI("1-(-2)^3") << endl;     // 1-(-8)=9
    cout << evaluateExpressionI("1-(-2)^-3") << endl;    // 1-(-1/8)=1.125
    cout << evaluateExpressionI("1-(-2)^-3^-2") << endl; // 1-(-2)^(1/9) gives a complex no.
    cout << evaluateExpressionI("1-(-2)^-3^2") << endl;  // 1-(-2)^9=1-(-512)=1+512=513
    cout << evaluateExpressionI("1-(-2)^0.5") << endl;   // sqrt(-2) is a complex no.
    cout << evaluateExpressionI("1-(-2)^-2") << endl;    // 1-1/4=0.75
    cout << "-------------Function tests--------------" << endl;
    cout << evaluateExpressionI("sin(30)*2") << endl;       // 1/2*2=1
    cout << evaluateExpressionI("-sin(30*1)") << endl;      // -0.5
    cout << evaluateExpressionI("sin(30)") << endl;         // 0.5
    cout << evaluateExpressionI("cos(sin(30))") << endl;    // cos0.5deg
    cout << evaluateExpressionI("tan(sin(30))") << endl;    // tan0.5
    cout << evaluateExpressionI("sin(30)/cos(30)") << endl; // =tan30=
    cout << evaluateExpressionI("sin(30^2)") << endl;
    cout << evaluateExpressionI("sin(30+3)-(-3*cos(50))") << endl;
    cout << evaluateExpressionI("cos(sin(30))") << endl;    // cos0.5deg <= 1
    cout << evaluateExpressionI("cos(sin(30)+30)") << endl; // cos30.5deg >= sqrt(3)/2
    cout << "-------------Important tests--------------" << endl;
    cout << evaluateExpressionI("-(+8 .8 8)+(9)-3 +(2^-5) -(-(+10))-loge(778.887 77)") << endl; // 0.493383
    cout << evaluateExpressionI("-(+8 .8 8) -loge(778.887 77)") << endl;                        // -15.5379
    cout << evaluateExpressionI("3^ log(4, 4)"s) << endl;                                       // 3
    cout << evaluateExpressionI("log 2(3 ^ log(4,4))"s) << endl;                                // ~1.58
    cout << evaluateExpressionI("log2(8)"s) << endl;                                            // 3
    cout << evaluateExpressionI("log2(6)"s) << endl;                                            // 2.584
    cout << evaluateExpressionI("log2(3^log(4,4)+log2(8))"s) << endl;                           // 2.584
    cout << evaluateExpressionI("log2(3^log(4,4)+log2(8))^0.8"s) << endl;                       // 2.13
    cout << evaluateExpressionI("log2(2)"s) << endl;                                            // 1
    cout << evaluateExpressionI("log2(3^log(4,4)+log2(8))^0.8+log2(2)"s) << endl;               // 3.13

    cout << evaluateExpressionI("log2(3^log2(4)+log2(8))^0.8+log2(2)") << endl;                                  // 3.77
    cout << evaluateExpressionI("log2(2^log(loge(555),4)+log2(8))^0.8+log2(2)"s) << endl;                        // 3.05673
    cout << evaluateExpressionI("-2^-2^1+log2(2^-4*4)^1^log2(2^log(loge(555),4)+log2(8))^0.8+log2(2)"s) << endl; // -0.75
    cout << evaluateExpressionI("-2^-2^1+log2(2^-4*4)^1^log2(2^log(4,4)+log2(8))^0.8+log2(2)"s) << endl;         // -0.75
}

// Double tests:
// 2.992
// 3
// 23
// -2
// 3
// 1
// 3
// 3
// 3
// 9
// -3
// 13
// 32.0227
// -63
// 9
// 513
// 2.41785e+24
// -65535
// -9
// 23
// -23
// -38
// -58
// 158
// -30
// -900
// -27000
// 900
// ############ part-2 ###############
// -4
// 0.875
// 9
// 1.125
// bad input!
// 0
// 513
// bad input!
// 0
// 0.75
// -----------Functions now--------------
// Wrong syntax or unknown symbols in the input!
// bad input!
// 0
// Wrong syntax or unknown symbols in the input!
// bad input!
// 0
// Wrong syntax or unknown symbols in the input!
// bad input!
// 0
// Wrong syntax or unknown symbols in the input!
// bad input!
// 0
// Wrong syntax or unknown symbols in the input!
// bad input!
// 0
// Wrong syntax or unknown symbols in the input!
// bad input!
// 0
// Wrong syntax or unknown symbols in the input!
// bad input!
// 0
// bad input!
// 0
// Wrong syntax or unknown symbols in the input!
// bad input!
// 0
// Wrong syntax or unknown symbols in the input!
// bad input!
// 0
// -------------Correction tests--------------
// 1
// -0.5
// 0.5
// 0.999962
// 0.00872687
// 0.57735
// 6.12323e-16
// 2.473
// 0.999962
// 0.861629
// -------------Important tests--------------
// 0.493383
// -15.5379
// 3
// 1.58496
// 3
// 2.58496
// 2.58496
// 2.13778
// 1
// 3.13778
// 3.77708
// 3.05673
// -0.75
// -0.75

// BigInteger implementation tests:
// 3
// 23
// -2
// 3
// 1
// 0
// 3
// 3
// 9
// -3
// 13
// 32
// -63
// 9
// 513
// 2417851639229258349412353
// -65535
// -9
// 23
// -23
// -38
// -58
// 158
// -30
// -900
// -27000
// 900
// ############ part-2 ###############
// -4
// bad input!
// 0
// 9
// bad input!
// 0
// bad input!
// 0
// 513
// bad input!
// 0
// bad input!
// 0

// Matrix operator tests:
// 4 2
// 1.1 2.2
// 2.3 4.1
// 5.6 7
// 8 4
// 2 6
// 1 2 3 4 5 6
// 7 8 9 10 11 12
// 6 3
// 4.3 4.4 4.5
// 4.6 4.7 4.8
// 9.9 10 10.1
// 10.2 10.3 10.4
// 11 12 13
// 9 1 1
// 3 5
// 2 2 2 2 2
// 1 1 2 1 3
// 5 3 2 1 4
// Multiplications: 106, in the order: (0*((1*2)*3))
// 9106.68 6914.16 6875.88 4721.64 10126.4
// 17302 13137.5 13064.6 8972.92 19238.6
// 31752 24116.4 23982 16480.8 35301
// 24489.6 18619.2 18513.6 12748.8 27213.6