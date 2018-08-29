/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package listaclientes;

import java.util.Scanner;

/**
 *
 * @author vinicius
 */
public class Nacionalidade {
    public String Pais;
    public String Sigla;
    public String cod_pais;

    Scanner entrada = new Scanner(System.in);
    
    public String getCod_pais() {
        return cod_pais;
    }

    public void setCod_pais() {
          do{
            System.out.println("Informe o código do seu Pais");
            cod_pais = entrada.next();
        }while(cod_pais.length() > 4);
    }
    
    
    public Nacionalidade(String Pais, String Sigla, String cod_pais){
        this.Pais = Pais;
        this.Sigla = Sigla;
        this.cod_pais = cod_pais;
    }

    public String getSigla() {
        return Sigla;
    }

    public void setSigla() {
        do{
            System.out.println("Informe a sigla de seu Pais");
            Sigla = entrada.next();
        }while(Sigla.length() < 2);
        
    }

    public String getPais() {
        return Pais;
    }

    public void setPais(String Pais) {
        this.Pais = Pais;
    }
    
}
