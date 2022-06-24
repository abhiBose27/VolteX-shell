/*#include <stdlib.h>
#include <stdio.h>
#include "cmat.h"
*/

#include "headers.h"
void cmat(int nb_par)
{

    if (nb_par > 1)
    {
        printf("ERROR: Too many Arguments. Type 'help cmat' to know more.\n");
        return;
    }
    system("./matrix");
}
