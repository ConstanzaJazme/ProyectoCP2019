#include <iostream>
#include <xlnt/xlnt.hpp>
#include <vector>
#include <string>

using namespace std;

int main()
{
        //creacion de archivo Start
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

        //Terminar creacion de archivo END
        //Colocar nombres pestañas
        xlnt::workbook salida;
        salida.load(dest_filename);

        xlnt::worksheet hojaActiva = salida.sheet_by_index(0);
        hojaActiva.title("M1-301");

        salida.save(dest_filename);

        return 0;
}
