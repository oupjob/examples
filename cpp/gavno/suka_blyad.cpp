#include<iostream>

void suka( void(*callback)( void(*)( void(*)() ) ) ) {
    std::cout << "Suka, ";
    callback( suka );
} 

void blyad( void(*callback)( void(*)( void(*)() ) ) ) {
    std::cout << "Blyad !!!" << std::endl;
    callback( blyad );
} 

int main() {
    suka( blyad );
    return 0;
}