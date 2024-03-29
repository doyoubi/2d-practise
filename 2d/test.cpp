#include<iostream>
using std::cout;
using std::cin;
using std::endl;

#include"2d.h"
using namespace _2d;

bool all_test_pass = true;
void check(bool to_check)
{
    if(to_check) cout<<"true"<<endl;
    else { cout<<"false"<<endl; all_test_pass = false; }
}

bool test_conversion()
{
    cout<<"test conversion:"<<endl;
    Vector_2d<double> v_double(1.0,1.0);
    Vector_2d<int> v_int(2,1);
    check(v_double + v_int == Vector_2d<double>(3.0,2.1));
    check(v_double - v_int == Vector_2d<double>(-1.0,0.0));
    check(v_double * v_int == 3.0);
    check(v_int * 2.0 == Vector_2d<double>(4.0,2.0)); 
    check(v_double * 2 == Vector_2d<double>(2,2));
    check(v_int * 2.0 == Vector_2d<int>(4.0,2.0)); 
    check(v_double * 2 == Vector_2d<int>(2,2));
    cout<<endl;
    return all_test_pass;
}

bool test_assignment()
{
    {
        cout<<"test assignment"<<endl;
        // int
        Vector_2d<int> v1(1,2);
        Vector_2d<int> v2 = v1;
        check(v2 == v1);

        v1 += v2;
        check(v1 == Vector_2d<int>(2,4));

        v1 -= v2;
        check(v1 == Vector_2d<int>(1,2));

        v1 *= 2;
        check(v1 == Vector_2d<int>(2,4));
    }
    // double
    {
        Vector_2d<double> v1(1,2);
        Vector_2d<double> v2 = v1;
        check(v2 == v1);

        v1 += v2;
        check(v1 == Vector_2d<double>(2,4));

        v1 -= v2;
        check(v1 == Vector_2d<double>(1,2));

        v1 *= 2;
        check(v1 == Vector_2d<double>(2,4));
        cout<<endl;
    }
    return all_test_pass;
}

bool test_basic_operator_double()
{
    Vector_2d<double> v1(1.0,1.0);
    Vector_2d<double> v2(2.0,-1.0);

    cout<<"test operator == : ";
    check(v1 == Vector_2d<double>(1,1));

    cout<<"test operator + : ";
    check(v1 + v2 == Vector_2d<double>(3, 0));

    cout<<"test operator - : ";
    check(v1 - v2 == Vector_2d<double>(-1, 2));

    cout<<"test operator vector * vector: ";
    check(v1 * v2 == 1);

    cout<<"test operator number * vector: ";
    check(v1 * 2 == Vector_2d<double>(2,2));
    
    cout<<"test operator vector * number: ";
    check(2 * v1 == Vector_2d<double>(2,2));

    cout<<"test operator = : ";
    v2 = v1;
    check(v1 == v2);

    cout<<"test operator += :";
    v1 = Vector_2d<double>(1,1);
    v1 += Vector_2d<double>(1,1);
    check(v1 == Vector_2d<double>(2,2));

    cout<<"test operator -= :";
    v1 = Vector_2d<double>(1,1);
    v1 -= Vector_2d<double>(1,1);
    check(v1 == Vector_2d<double>(0,0));

    cout<<endl;
    return all_test_pass;
}

bool test_basic_operator_int()
{
    Vector_2d<int> v1(1,1);
    Vector_2d<int> v2(2,-1);

    cout<<"test operator == : ";
    check(v1 == Vector_2d<int>(1,1));

    cout<<"test operator + : ";
    check(v1 + v2 == Vector_2d<int>(3, 0));

    cout<<"test operator - : ";
    check(v1 - v2 == Vector_2d<int>(-1, 2));

    cout<<"test operator vector * vector: ";
    check(v1 * v2 == 1);

    cout<<"test operator number * vector: ";
    check(v1 * 2 == Vector_2d<int>(2,2));
    
    cout<<"test operator vector * number: ";
    check(2 * v1 == Vector_2d<int>(2,2));

    cout<<"test operator = : ";
    v2 = v1;
    check(v1 == v2);

    cout<<"test operator += :";
    v1 = Vector_2d<int>(1,1);
    v1 += Vector_2d<int>(1,1);
    check(v1 == Vector_2d<int>(2,2));

    cout<<"test operator -= :";
    v1 = Vector_2d<int>(1,1);
    v1 -= Vector_2d<int>(1,1);
    check(v1 == Vector_2d<int>(0,0));

    cout<<endl;
    return all_test_pass;
}


bool test_const()
{
    // test whether const work
    // const Image<int> const_image;
    // const_image[0][0] = 0;
}

bool test_image()
{
    int width = 5, height = 3;
    Image<int> image1;
    image1.create(width, height);
    Image<int> image2(width, height);

    int num = 0;
    for(int x = 0; x < width; ++x)
        for(int y = 0; y < height; ++y)
        {
            image1[x][y] = num;
            image2[x][y] = num;
            ++num;
        }
    image1.output();
    image2.output();
    check(image1.get_width() == width);
    check(image1.get_height() == height);
    cout<<endl;
    return all_test_pass;
}

int main()
{
    test_assignment();
    test_basic_operator_double();
    test_basic_operator_int();
    test_image();
    test_conversion();
    if(all_test_pass)
        cout<<"all test pass!"<<endl;
    else 
        cout<<"some test fall!!!"<<endl;
    cout<<endl;
    return 0;
}
