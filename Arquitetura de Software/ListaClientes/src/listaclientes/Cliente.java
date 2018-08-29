/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package listaclientes;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

/**
 *
 * @author Ricardo Santos
 */
public class Cliente {    
    private String nome;            
    private String telefone;
    private String pais;     
    private int idade;
    double credito;
    Scanner entrada = new Scanner(System.in);
    
    public Cliente( String nome, String telefone, String pais,int idade, double credito) {
        this.nome = nome;
        this.telefone = telefone;
        this.pais = pais;
        this.idade = idade;
        this.credito = credito;
    }
    
// Métodos getters and setters
    void setNome()
    {
    /*
       O nome do cliente não pode ser menor que 5 caracteres 
    */
        do
        {    
            System.out.print("Informe um nome: ");
            nome = entrada.nextLine();
            if(nome.length() < 5)
            {
                System.out.println("O nome deve ser maior/igual 5 caracteres!!!");
            }
        }while(nome.length() < 5);
    }

    void setTelefone()
    {
        do{
            System.out.print("Informe o telefone: ");
            telefone = entrada.next();
            if(telefone.length() < 7 && telefone.length() > 10){
                System.out.println("Telefone invalido");
            }
        }while(telefone.length() < 7 || telefone.length() > 15);
    }
    void setPais()
    {
        System.out.print("Informe o Pais: ");
        pais = entrada.next();
        
        /*Se o cliente morar no Brasil, ele terá um crédito adicional de R$ 100,00, 
        independente da idade;
        o campo país não pode ser nulo/vazio;*/
        
        
        if("Brasil".equals(pais))
        {
            credito = 100.00;
        }
    }
    void setIdade()
    {
        System.out.print("Informe a idade: ");
        idade = entrada.nextInt();
        /* O limite de crédito é dado automaticamente de acordo com a idade: 
        Para clientes até 18 anos o limite é R$ 100,00. Entre 18 e 35 é R$ 300,00. 
        Acima de 35 é R$ 500,00;*/
        if(idade <= 18 )
        {
            credito += 100.00;
        }
        else if(idade > 18 && idade < 35)
        {
            credito +=  300.00;
        }
        else if(idade > 35)
        {
            credito += 500.00;
        }
    }
    int getIdade() {
        return idade;
    }
    String getPais() {
        return pais;
    }
    String getNome() {
        return nome;
    }
    String getTelefone() {
        return telefone;
    }
    double getCredito()
    {
        return credito;
    }



}