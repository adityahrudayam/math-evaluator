#include "EvaluateExpressionD.hpp"
#include "EvaluateExpressionI.hpp"
#include "ExpressionEvaluator.hpp"
#include "MatrixOperator.hpp"
#include <cmath>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

void test()
{
    // LoadLDMFromFile("./matrices.txt");
    string temp[6] = {"1", "2", "3", "4", "5", "6"};
    MatrixLD mat('\02', '\03', temp);
    cout << mat << endl;
    takeInputAndEvalLD();
    takeInputAndEvalLL();
    takeInputAndEvalBI();

    cout << evaluateExpression(" 2-1 + 2 \n");            // 3
    cout << evaluateExpression("(1+(4+5+2)-3)+(6+8)\n");  // 23
    cout << evaluateExpression("- 2\n");                  // -2
    cout << evaluateExpression("- (2) - (-3+4 - (6))\n"); // 3
    cout << evaluateExpression("1\n");                    // 1
    cout << evaluateExpression("1/3*9\n");                // 0
    cout << evaluateExpression("9*1/3\n");                // 3
    cout << evaluateExpression("1-(     -2)\n");          // 3
    cout << evaluateExpression("1-(     -2)^3\n");        // 1-(-8)=9
    cout << evaluateExpression("1*5     -2^3\n");         // 5-8=-3
    cout << evaluateExpression("1*5-(     -2)^3\n");      // 5-(-8)=13
    cout << evaluateExpression("1/44-(     -2)^5\n");     // 32
    cout << evaluateExpression("1-(     -2)^6\n");        // 1-64=-63
    cout << evaluateExpression("1-(     -2)^3\n");        // 1-(-8)=9
    cout << evaluateExpression("1-(     -2)^3^2\n");      // 1-(-2)^9=1-(-512)=513
    cout << evaluateExpression("1-(     -2)^3^2^2\n");    // 1-(-2)^(3^4)
    cout << evaluateExpression("1-(     -2)^2^2^2\n");    // 1-(-2)^16 = 1-65536=-65535
    cout << evaluateExpression("-1+(     -2)^3\n");       // -1+(-8)=-9
    cout << evaluateExpression("(3-(5-(8)-(2+(9-(0-(8-(2))))-(4))-(4)))\n");
    cout << evaluateExpression("-(3-(5-(8)-(2+(9-(0-(8-(2))))-(4))-(4)))\n");
    cout << evaluateExpression("-(3*(5-(-8)-(-2+(9-(0-(8/(-2))))-(4)))+(-4))\n");
    cout << evaluateExpression("-(3*(5-(-8)-(-2+(9-(0-(8/(-2))))-(4)))+(-4)^2)\n");
    cout << evaluateExpression("-(3*(5-(-8)^2-(-2+(9-(0-(8/(-2))))-(4)))+(-4)^2)\n");
    cout << evaluateExpression("-(3*(5-(-8)-(-2+(9-(0-(8/(-2))))-(4))+(-4)))\n");
    cout << evaluateExpression("-(3*(5-(-8)-(-2+(9-(0-(8/(-2))))-(4))+(-4)))^2\n");
    cout << evaluateExpression("-(3*(5-(-8)-(-2+(9-(0-(8/(-2))))-(4))+(-4)))^3\n");
    cout << evaluateExpression("(-(3*(5-(-8)-(-2+(9-(0-(8/(-2))))-(4))+(-4))))^2\n");
    cout << "############ part-2 ###############" << endl;
    cout << evaluateExpression("1-2-3\n");        //-4
    cout << evaluateExpression("1-2^-3\n");       // 1-1/8=0.875
    cout << evaluateExpression("1-(-2)^3\n");     // 1-(-8)=9
    cout << evaluateExpression("1-(-2)^-3\n");    // 1-(-1/8)=1.125
    cout << evaluateExpression("1-(-2)^-3^-2\n"); // 1-(-2)^(1/9) gives a complex no.
    cout << evaluateExpression("1-(-2)^-3^2\n");  // 1-(-2)^9=1-(-512)=1+512=513
    cout << evaluateExpression("1-(-2)^0.5\n");   // sqrt(-2) is a complex no.
    cout << evaluateExpression("1-(-2)^-2\n");    // 1-1/4=0.75
    cout << "-------------Function tests--------------" << endl;
    cout << evaluateExpression("sin(30)*2\n");       // 1/2*2=1
    cout << evaluateExpression("-sin(30*1)\n");      // -0.5
    cout << evaluateExpression("sin(30)\n");         // 0.5
    cout << evaluateExpression("cos(sin(30))\n");    // cos0.5deg
    cout << evaluateExpression("tan(sin(30))\n");    // tan0.5
    cout << evaluateExpression("sin(30)/cos(30)\n"); // =tan30=
    cout << evaluateExpression("sin(30^2)\n");
    cout << evaluateExpression("sin(30+3)-(-3*cos(50))\n");
    cout << evaluateExpression("cos(sin(30))\n");    // cos0.5deg <= 1
    cout << evaluateExpression("cos(sin(30)+30)\n"); // cos30.5deg >= sqrt(3)/2
    cout << "-------------Important tests--------------" << endl;
    cout << evaluateExpression("-(+8 .8 8)+(9)-3 +(2^-5) -(-(+10))-loge(778.887 77)\n"); // 0.493383
    cout << evaluateExpression("-(+8 .8 8) -loge(778.887 77)\n");                        // -15.5379
    cout << evaluateExpression("3^ log(4, 4)\n");                                        // 3
    cout << evaluateExpression("log 2(3 ^ log(4,4))\n");                                 // ~1.58
    cout << evaluateExpression("log2(8)\n");                                             // 3
    cout << evaluateExpression("log2(6)\n");                                             // 2.584
    cout << evaluateExpression("log2(3^log(4,4)+log2(8))\n");                            // 2.584
    cout << evaluateExpression("log2(3^log(4,4)+log2(8))^0.8\n");                        // 2.13
    cout << evaluateExpression("log2(2)\n");                                             // 1
    cout << evaluateExpression("log2(3^log(4,4)+log2(8))^0.8+log2(2)\n");                // 3.13

    cout << evaluateExpression("log2(3^log2(4)+log2(8))^0.8+log2(2)\n");                                 // 3.77
    cout << evaluateExpression("log2(2^log(loge(555),4)+log2(8))^0.8+log2(2)\n");                        // 3.05673
    cout << evaluateExpression("-2^-2^1+log2(2^-4*4)^1^log2(2^log(loge(555),4)+log2(8))^0.8+log2(2)\n"); // -0.75
    cout << evaluateExpression("-2^-2^1+log2(2^-4*4)^1^log2(2^log(4,4)+log2(8))^0.8+log2(2)\n");         // -0.75

    cout << "--------------------------------------------" << endl;

    cout << evaluateExpressionD("1    + 2  - 0.008\n");
    cout << evaluateExpressionD(" 2-1 + 2 \n");
    cout << evaluateExpressionD("(1+(4+5+2)-3)+(6+8)\n");
    cout << evaluateExpressionD("- 2\n");
    cout << evaluateExpressionD("- (2) - (-3+4 - (6))\n");
    cout << evaluateExpressionD("1\n");
    cout << evaluateExpressionD("1/3*9\n");             // 0
    cout << evaluateExpressionD("9*1/3\n");             // 3
    cout << evaluateExpressionD("1-(     -2)\n");       // 3
    cout << evaluateExpressionD("1-(     -2)^3\n");     // 1-(-8)=9
    cout << evaluateExpressionD("1*5     -2^3\n");      // 5-8=-3
    cout << evaluateExpressionD("1*5-(     -2)^3\n");   // 5-(-8)=13
    cout << evaluateExpressionD("1/44-(     -2)^5\n");  // 32
    cout << evaluateExpressionD("1-(     -2)^6\n");     // 1-64=-63
    cout << evaluateExpressionD("1-(     -2)^3\n");     // 1-(-8)=9
    cout << evaluateExpressionD("1-(     -2)^3^2\n");   // 1-(-2)^9=1-(-512)=513
    cout << evaluateExpressionD("1-(     -2)^3^2^2\n"); // 1-(-2)^(3^4) - out of bounds
    cout << evaluateExpressionD("1-(     -2)^2^2^2\n"); // 1-(-2)^16 = 1-65536=-65535
    cout << evaluateExpressionD("-1+(     -2)^3\n");    // -1+(-8)=-9
    cout << evaluateExpressionD("(3-(5-(8)-(2+(9-(0-(8-(2))))-(4))-(4)))\n");
    cout << evaluateExpressionD("-(3-(5-(8)-(2+(9-(0-(8-(2))))-(4))-(4)))\n");
    cout << evaluateExpressionD("-(3*(5-(-8)-(-2+(9-(0-(8/(-2))))-(4)))+(-4))\n");
    cout << evaluateExpressionD("-(3*(5-(-8)-(-2+(9-(0-(8/(-2))))-(4)))+(-4)^2)\n");
    cout << evaluateExpressionD("-(3*(5-(-8)^2-(-2+(9-(0-(8/(-2))))-(4)))+(-4)^2)\n");
    cout << evaluateExpressionD("-(3*(5-(-8)-(-2+(9-(0-(8/(-2))))-(4))+(-4)))\n");
    cout << evaluateExpressionD("-(3*(5-(-8)-(-2+(9-(0-(8/(-2))))-(4))+(-4)))^2\n");
    cout << evaluateExpressionD("-(3*(5-(-8)-(-2+(9-(0-(8/(-2))))-(4))+(-4)))^3\n");
    cout << evaluateExpressionD("(-(3*(5-(-8)-(-2+(9-(0-(8/(-2))))-(4))+(-4))))^2\n");
    cout << "############ part-2 ###############" << endl;
    cout << evaluateExpressionD("1-2-3\n");        //-4
    cout << evaluateExpressionD("1-2^-3\n");       // 1-1/8=0.875
    cout << evaluateExpressionD("1-(-2)^3\n");     // 1-(-8)=9
    cout << evaluateExpressionD("1-(-2)^-3\n");    // 1-(-1/8)=1.125
    cout << evaluateExpressionD("1-(-2)^-3^-2\n"); // 1-(-2)^(1/9) gives a complex no.
    cout << evaluateExpressionD("1-(-2)^-3^2\n");  // 1-(-2)^9=1-(-512)=1+512=513
    cout << evaluateExpressionD("1-(-2)^0.5\n");   // sqrt(-2) is a complex no.
    cout << evaluateExpressionD("1-(-2)^-2\n");    // 1-1/4=0.75
    cout << "-------------Function tests--------------" << endl;
    cout << evaluateExpressionD("sin(30)*2\n");       // 1/2*2=1
    cout << evaluateExpressionD("-sin(30*1)\n");      // -0.5
    cout << evaluateExpressionD("sin(30)\n");         // 0.5
    cout << evaluateExpressionD("cos(sin(30))\n");    // cos0.5deg
    cout << evaluateExpressionD("tan(sin(30))\n");    // tan0.5
    cout << evaluateExpressionD("sin(30)/cos(30)\n"); // =tan30=
    cout << evaluateExpressionD("sin(30^2)\n");
    cout << evaluateExpressionD("sin(30+3)-(-3*cos(50))\n");
    cout << evaluateExpressionD("cos(sin(30))\n");    // cos0.5deg <= 1
    cout << evaluateExpressionD("cos(sin(30)+30)\n"); // cos30.5deg >= sqrt(3)/2
    cout << "-------------Important tests--------------" << endl;
    cout << evaluateExpressionD("-(+8 .8 8)+(9)-3 +(2^-5) -(-(+10))-loge(778.887 77)\n"); // 0.493383
    cout << evaluateExpressionD("-(+8 .8 8) -loge(778.887 77)\n");                        // -15.5379
    cout << evaluateExpressionD("3^ log(4, 4)\n");                                        // 3
    cout << evaluateExpressionD("log 2(3 ^ log(4,4))\n");                                 // ~1.58
    cout << evaluateExpressionD("log2(8)\n");                                             // 3
    cout << evaluateExpressionD("log2(6)\n");                                             // 2.584
    cout << evaluateExpressionD("log2(3^log(4,4)+log2(8))\n");                            // 2.584
    cout << evaluateExpressionD("log2(3^log(4,4)+log2(8))^0.8\n");                        // 2.13
    cout << evaluateExpressionD("log2(2)\n");                                             // 1
    cout << evaluateExpressionD("log2(3^log(4,4)+log2(8))^0.8+log2(2)\n");                // 3.13

    cout << evaluateExpressionD("log2(3^log2(4)+log2(8))^0.8+log2(2)\n");                                     // 3.77
    cout << evaluateExpressionD("log2(2^log(loge(555),4)+log2(8))^0.8+log2(2)\n");                            // 3.05673
    cout << evaluateExpressionD("-2^-2^1+log2(2^-4*4)^1^log2(2^log(loge(555),4)+log2(8))^0.8+log2(2)\n");     // -0.75
    cout << evaluateExpressionD("-2^-2^1+log2(2^-4*4)^1^log2(2^log(4,4)+log2(8))^0.8+log2(2)\n");             // -0.75
    cout << evaluateExpressionD("-02^-002^1+log2(2^-004*4)^1^log2(002^log(4,4)+log2(8))^000.08+log2(002)\n"); // -0.75
    cout << "--------------------------------------------" << endl;

    cout << evaluateExpressionI("1    + 2  - 0.008\n");
    cout << evaluateExpressionI(" 2-1 + 2 \n");
    cout << evaluateExpressionI("(1+(4+5+2)-3)+(6+8)\n");
    cout << evaluateExpressionI("- 2\n");
    cout << evaluateExpressionI("- (2) - (-3+4 - (6))\n");
    cout << evaluateExpressionI("1\n");
    cout << evaluateExpressionI("1/3*9\n");             // 0
    cout << evaluateExpressionI("9*1/3\n");             // 3
    cout << evaluateExpressionI("1-(     -2)\n");       // 3
    cout << evaluateExpressionI("1-(     -2)^3\n");     // 1-(-8)=9
    cout << evaluateExpressionI("1*5     -2^3\n");      // 5-8=-3
    cout << evaluateExpressionI("1*5-(     -2)^3\n");   // 5-(-8)=13
    cout << evaluateExpressionI("1/44-(     -2)^5\n");  // 32
    cout << evaluateExpressionI("1-(     -2)^6\n");     // 1-64=-63
    cout << evaluateExpressionI("1-(     -2)^3\n");     // 1-(-8)=9
    cout << evaluateExpressionI("1-(     -2)^3^2\n");   // 1-(-2)^9=1-(-512)=513
    cout << evaluateExpressionI("1-(     -2)^3^2^2\n"); // 1-(-2)^(3^4) - out of bounds
    cout << evaluateExpressionI("1-(     -2)^2^2^2\n"); // 1-(-2)^16 = 1-65536=-65535
    cout << evaluateExpressionI("-1+(     -2)^3\n");    // -1+(-8)=-9
    cout << evaluateExpressionI("(3-(5-(8)-(2+(9-(0-(8-(2))))-(4))-(4)))\n");
    cout << evaluateExpressionI("-(3-(5-(8)-(2+(9-(0-(8-(2))))-(4))-(4)))\n");
    cout << evaluateExpressionI("-(3*(5-(-8)-(-2+(9-(0-(8/(-2))))-(4)))+(-4))\n");
    cout << evaluateExpressionI("-(3*(5-(-8)-(-2+(9-(0-(8/(-2))))-(4)))+(-4)^2)\n");
    cout << evaluateExpressionI("-(3*(5-(-8)^2-(-2+(9-(0-(8/(-2))))-(4)))+(-4)^2)\n");
    cout << evaluateExpressionI("-(3*(5-(-8)-(-2+(9-(0-(8/(-2))))-(4))+(-4)))\n");
    cout << evaluateExpressionI("-(3*(5-(-8)-(-2+(9-(0-(8/(-2))))-(4))+(-4)))^2\n");
    cout << evaluateExpressionI("-(3*(5-(-8)-(-2+(9-(0-(8/(-2))))-(4))+(-4)))^3\n");
    cout << evaluateExpressionI("(-(3*(5-(-8)-(-2+(9-(0-(8/(-2))))-(4))+(-4))))^2\n");
    cout << "############ part-2 ###############" << endl;
    cout << evaluateExpressionI("1-2-3\n");        //-4
    cout << evaluateExpressionI("1-2^-3\n");       // 1-1/8=0.875
    cout << evaluateExpressionI("1-(-2)^3\n");     // 1-(-8)=9
    cout << evaluateExpressionI("1-(-2)^-3\n");    // 1-(-1/8)=1.125
    cout << evaluateExpressionI("1-(-2)^-3^-2\n"); // 1-(-2)^(1/9) gives a complex no.
    cout << evaluateExpressionI("1-(-2)^-3^2\n");  // 1-(-2)^9=1-(-512)=1+512=513
    cout << evaluateExpressionI("1-(-2)^0.5\n");   // sqrt(-2) is a complex no.
    cout << evaluateExpressionI("1-(-2)^-2\n");    // 1-1/4=0.75
    cout << "-------------Function tests--------------" << endl;
    cout << evaluateExpressionI("sin(30)*2\n");       // 1/2*2=1
    cout << evaluateExpressionI("-sin(30*1)\n");      // -0.5
    cout << evaluateExpressionI("sin(30)\n");         // 0.5
    cout << evaluateExpressionI("cos(sin(30))\n");    // cos0.5deg
    cout << evaluateExpressionI("tan(sin(30))\n");    // tan0.5
    cout << evaluateExpressionI("sin(30)/cos(30)\n"); // =tan30=
    cout << evaluateExpressionI("sin(30^2)\n");
    cout << evaluateExpressionI("sin(30+3)-(-3*cos(50))\n");
    cout << evaluateExpressionI("cos(sin(30))\n");    // cos0.5deg <= 1
    cout << evaluateExpressionI("cos(sin(30)+30)\n"); // cos30.5deg >= sqrt(3)/2
    cout << "-------------Important tests--------------" << endl;
    cout << evaluateExpressionI("-(+8 .8 8)+(9)-3 +(2^-5) -(-(+10))-loge(778.887 77)\n"); // 0.493383
    cout << evaluateExpressionI("-(+8 .8 8) -loge(778.887 77)\n");                        // -15.5379
    cout << evaluateExpressionI("3^ log(4, 4)\n");                                        // 3
    cout << evaluateExpressionI("log 2(3 ^ log(4,4))\n");                                 // ~1.58
    cout << evaluateExpressionI("log2(8)\n");                                             // 3
    cout << evaluateExpressionI("log2(6)\n");                                             // 2.584
    cout << evaluateExpressionI("log2(3^log(4,4)+log2(8))\n");                            // 2.584
    cout << evaluateExpressionI("log2(3^log(4,4)+log2(8))^0.8\n");                        // 2.13
    cout << evaluateExpressionI("log2(2)\n");                                             // 1
    cout << evaluateExpressionI("log2(3^log(4,4)+log2(8))^0.8+log2(2)\n");                // 3.13

    cout << evaluateExpressionI("log2(3^log2(4)+log2(8))^0.8+log2(2)\n");                                 // 3.77
    cout << evaluateExpressionI("log2(2^log(loge(555),4)+log2(8))^0.8+log2(2)\n");                        // 3.05673
    cout << evaluateExpressionI("-2^-2^1+log2(2^-4*4)^1^log2(2^log(loge(555),4)+log2(8))^0.8+log2(2)\n"); // -0.75
    cout << evaluateExpressionI("-2^-2^1+log2(2^-4*4)^1^log2(2^log(4,4)+log2(8))^0.8+log2(2)\n");         // -0.75
}

char run()
{
    cout << "1: write and evaluate an integer (not big numbers) math expression\n";
    cout << "2: write and evaluate a big integer (1 to 10^5 digits at most) math expression\n";
    cout << "3: write and evaluate a decimal math expression\n";
    cout << "4: write matrices as input and add the matrices\n";
    cout << "5: write matrices as input and subtract the matrices\n";
    cout << "6: write matrices as input and multiply the matrices\n";
    cout << "7: read from a file and evaluate a math expression involving matrices\n";
    cout << "8: exit!" << endl;

    string inp;
    short opt;
    cin >> opt;
    switch (opt)
    {
    case 1:
        cout << "please enter an integer expression to evaluate." << endl;
        cin >> inp;
        cout << "result: " << evaluateExpressionI(inp) << endl;
        break;
    case 2:
        cout << "please enter a big integer expression to evaluate." << endl;
        cin >> inp;
        cout << "result: " << evaluateExpression(inp) << endl;
        break;
    case 3:
        cout << "please enter a decimal expression to evaluate." << endl;
        cin >> inp;
        cout << "result: " << evaluateExpressionD(inp) << endl;
        break;
    case 4:
        cout << "please enter the matrices expression to add." << endl;
        cin >> inp;
        cout << "result: " << evaluateExpressionD(inp) << endl;
        break;
    case 7:
        cout << "please enter a decimal expression to evaluate." << endl;
        cin >> inp;
        cout << "result: " << evaluateExpressionD(inp) << endl;
        break;
    case 8:
        cout << "EXITING..." << endl;
        break;
    default:
        cout << "please enter a valid option from 1 to 8!" << endl;
        break;
    }
    cout << endl;
    return opt;
}

int main(int argc, const char *argv[])
{
    while (run() != 8)
        ;
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
// -------------Function tests--------------
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
//-------------------------------------
// Integer tests:
// bad input!
// 0
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
// 1
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
// -7
// 9
// 9
// 513
// 513
// bad input!
// 0
// -3
// -------------Function tests--------------
// 0
// 0
// 0
// 1
// 0
// bad input!
// 0
// 0
// 0
// 1
// 0
// -------------Important tests--------------
// bad input!
// 0
// bad input!
// 0
// 3
// 1
// 3
// 2
// 2
// bad input!
// 0
// 1
// bad input!
// 0
// bad input!
// 0
// bad input!
// 0
// bad input!
// 0
// bad input!
// 0

// Matrix operator tests:
// 4
// 4 2
// -1.1 2.2
// 2.3 4.1
// 5.6 7
// 8 4
// 2 6
// 1 2 3 4 5 6
// 7 8 -9 10 11 12
// 6 3
// 4.3 4.4 4.5
// 4.6 4.7 4.8
// 9.9 10 10.1
// 10.2 -10.3 10.4
// 11 12 13
// 9 1 1
// 3 5
// 2 2 2 -2 2
// 1 1 2 1 3
// 5 3 2 1 4
// Multiplications: 106, in the order: (0*((1*2)*3))
// 2655.84 1954.04 1570.36 -616 2239.38
// 10341.8 7667.98 6568.4 -1845.74 9479.52
// 19730.8 14640.4 12615.1 -3419.64 18225.5
// 17224.8 12808.8 11227.2 -2724 16269.6

// 4
// 4 2
// -1 2
// 2 4
// 6 7
// 8 4
// 2 6
// 1 2 3 4 5 6
// 7 8 -9 10 11 12
// 6 3
// 4 4 5
// 5 5 5
// 9 10 10
// 10 10 11
// 11 12 13
// 9 1 1
// 3 5
// 2 2 2 -2 2
// 1 1 2 1 3
// 5 3 2 1 4

// 4
// 4 2
// -11 22
// 23 41
// 56 7
// 8 4
// 2 6
// 1 2 3 4 5 6
// 7 8 -9 10 11 12
// 6 3
// 4 43 45
// 6 76 84
// 99 10 111
// 17 -13 104
// 11 12 13
// 9 1 1
// 3 5
// 2 2 2 -2 2
// 1 1 2 1 3
// 5 3 2 1 4
// Multiplications: 106, in the order: (0*((1*2)*3))
// 59928 30602 31636 59444 76659
// 389388 244864 212252 123484 396426
// 398916 266658 219744 36288 371217
// 74736 48744 40992 13728 72228

// 4
// 4 2
// 121313124144 23454567678568585
// -230998989878 4
// 5 -7
// 8 4
// 2 6
// 1 2 3 4 5 6
// 7 8 9 10 11 12
// 6 3
// 4 4 5
// 6 7 8
// -9188886777773713749891 10 10
// 10 10 10
// 11 12 3145886777773713749891
// 9 1 1
// 3 5
// 2 2 2 2 2
// 1 1 2 1 3
// 5 3 2 1 4
// Multiplications: 106, in the order: (0*((1*2)*3))
// 178816038390918523645996370760736782812 -1444466893427581252369562123405757305504 -2256108359336831140367537342517141562956 -3067749825246081028385120617572251393820 -632825427518331364342174820378784687934
// -5431675315762379376938598505659644 1835291363323623965517533814416852 5468774702866625636710026130015560 9102258042409627307973666134493348 -1798191976219377705781680034500476
// 64202568445110945003590 391374793333577174995498 554960905777810289989296 718547018222043404987406 227788680889344059995232
// 218606033332114124985984 -309902945333869784999664 -574157434666861739989584 -838411923999853694985312 -45648456000877830001032

// 4
// 4 2
// -11 22
// 23 41
// 56 7
// 8 4
// 2 6
// 1 2 3 4 5 6
// 7 8 -9 10 11 12
// 6 3
// 4 43 45
// 6 76 84
// 99 10 111
// 17 -13 104
// 11 12 13
// 9 1 1
// 3 5
// 2 2 2 -2 2
// 1 1 2 1 3
// 5 3 2 1 4
// Multiplications: 106, in the order: (0*((1*2)*3))
// 59928 30602 31636 59444 76659
// 389388 244864 212252 123484 396426
// 398916 266658 219744 36288 371217
// 74736 48744 40992 13728 72228

// 4
// 4 2
// -11 22
// 23 41
// 56 7
// 8 4
// 2 6
// 1 2 3 4 5 6
// 7 8 -9 10 11 12
// 6 3
// 4 43 45
// 6 76 84
// 99 10 111
// 17 -13 104
// 11 12 13
// 9 1 1
// 3 5
// 2 2 2 -2 2
// 1 1 2 1 3
// 5 3 2 1 4
// Multiplications: 106, in the order: (0*((1*2)*3))
// 59928 30602 31636 59444 76659
// 389388 244864 212252 123484 396426
// 398916 266658 219744 36288 371217
// 74736 48744 40992 13728 72228

// 4
// 4 2
// -11 22
// 23 41
// 56 7
// 8 4
// 2 6
// 1 2 3 4 5 6
// 7 8 -9 10 11 12
// 6 3
// 4 43 45
// 6 76 84
// 99 10 111
// 17 -13 104
// 11 12 13
// 9 1 1
// 3 5
// 2 2 2 -2 2
// 1 1 2 1 3
// 5 3 2 1 4
// Multiplications: 106, in the order: (0*((1*2)*3))
// 59928 30602 31636 59444 76659
// 389388 244864 212252 123484 396426
// 398916 266658 219744 36288 371217
// 74736 48744 40992 13728 72228

// 4
// 4 2
// 121313124144 23454567678568585
// -230998989878 4
// 5 -7
// 8 4
// 2 6
// 1 2 3 4 5 6
// 7 8 9 10 11 12
// 6 3
// 4 4 5
// 6 7 8
// -9188886777773713749891 10 10
// 10 10 10
// 11 12 3145886777773713749891
// 9 1 1
// 3 5
// 2 2 2 2 2
// 1 1 2 1 3
// 5 3 2 1 4
// Multiplications: 106, in the order: (0*((1*2)*3))
// 1.78816e+38 -1.44447e+39 -2.25611e+39 -3.06775e+39 -6.32825e+38
// -5.43168e+33 1.83529e+33 5.46877e+33 9.10226e+33 -1.79819e+33
// 6.42026e+22 3.91375e+23 5.54961e+23 7.18547e+23 2.27789e+23
// 2.18606e+23 -3.09903e+23 -5.74157e+23 -8.38412e+23 -4.56485e+22

// 4
// 4 2
// 121313124144 23454567678568585
// -230998989878 4
// 5 -7
// 8 4
// 2 6
// 1 2 3 4 5 6
// 7 8 9 10 11 12
// 6 3
// 4 4 5
// 6 7 8
// -9188886777773713749891 10 10
// 10 10 10
// 11 12 3145886777773713749891
// 9 1 1
// 3 5
// 2 2 2 2 2
// 1 1 2 1 3
// 5 3 2 1 4
// Multiplications: 106, in the order: (0*((1*2)*3))
// 178816038390918523645996370760736782812 -1444466893427581252369562123405757305504 -2256108359336831140367537342517141562956 -3067749825246081028385120617572251393820 -632825427518331364342174820378784687934
// -5431675315762379376938598505659644 1835291363323623965517533814416852 5468774702866625636710026130015560 9102258042409627307973666134493348 -1798191976219377705781680034500476
// 64202568445110945003590 391374793333577174995498 554960905777810289989296 718547018222043404987406 227788680889344059995232
// 218606033332114124985984 -309902945333869784999664 -574157434666861739989584 -838411923999853694985312 -45648456000877830001032

// 4
// 4 2
// -1 2
// 2 4
// 6 7
// 8 4
// 2 6
// 1 2 3 4 5 6
// 7 8 -9 10 11 12
// 6 3
// 4 4 5
// 5 5 5
// 9 10 10
// 10 10 11
// 11 12 13
// 9 1 1
// 3 5
// 2 2 2 -2 2
// 1 1 2 1 3
// 5 3 2 1 4
// Multiplications: 106, in the order: (0*((1*2)*3))
// 2878 2198 2152 -250 3126
// 11076 8436 8304 -780 12132
// 22708 17288 17032 -1540 24906
// 19056 14496 14304 -1200 20952

// 4
// 4 2
// -1 2
// 2 4
// 6 7
// 8 4
// 2 6
// 1 2 3 4 5 6
// 7 8 -9 10 11 12
// 6 3
// 4 4 5
// 5 5 5
// 9 10 10
// 10 10 11
// 11 12 13
// 9 1 1
// 3 5
// 2 2 2 -2 2
// 1 1 2 1 3
// 5 3 2 1 4
// Multiplications: 106, in the order: (0*((1*2)*3))
// 2878 2198 2152 -250 3126
// 11076 8436 8304 -780 12132
// 22708 17288 17032 -1540 24906
// 19056 14496 14304 -1200 20952

// 4
// 4 2
// -1 2
// 2 4
// 6 7
// 8 4
// 2 6
// 1 2 3 4 5 6
// 7 8 -9 10 11 12
// 6 3
// 4 4 5
// 5 5 5
// 9 10 10
// 10 10 11
// 11 12 13
// 9 1 1
// 3 5
// 2 2 2 -2 2
// 1 1 2 1 3
// 5 3 2 1 4
// Multiplications: 106, in the order: (0*((1*2)*3))
// 2878 2198 2152 -250 3126
// 11076 8436 8304 -780 12132
// 22708 17288 17032 -1540 24906
// 19056 14496 14304 -1200 20952
