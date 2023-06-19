#include <conio.h>
#include <math.h>


int main() {
int angle = 0;
double x, y;

for (x=0; x<=0.02; x+=0.001)
{
	y=sin(3.141*x/180);
	printf("%lf\n",y);
}

return 0;
}
