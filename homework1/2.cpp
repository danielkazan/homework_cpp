#include <math.h>
#include <iostream>

int main()
{
    int a, b, c;
    std::cin >> a >> b >> c;

    double d = b * b - (4 * a * c);
    double root1, root2;

    if (d < 0)
        std::cout << -1;

   root1 = (-b + sqrt(d)) / 2*a;
   root2 = (-b - sqrt(d)) / 2*a;

   std::cout << root1 << " " << root2;
}
