#include <iostream>
#include <xlnt/xlnt.hpp>
#include <vector>
#include <string>

using namespace std;

int main()
{

        xlnt::workbook wbOut;
        string dest_filename = "salida.xlsx";
        for(int i = 0; i < 17; i++) {
                wbOut.create_sheet();
        }
        // wbOut.create_sheet(); //here fail

        wbOut.save(dest_filename);

        xlnt::workbook resultado;
        resultado.load(dest_filename);
        for(int i = 0; i < 13; i++) {
                resultado.create_sheet();
        }
        resultado.save(dest_filename);

        xlnt::workbook resultado2;
        resultado2.load(dest_filename);
        for(int i = 0; i < 10; i++) {
                resultado2.create_sheet();
        }
        resultado2.save(dest_filename);

        return 0;
}
