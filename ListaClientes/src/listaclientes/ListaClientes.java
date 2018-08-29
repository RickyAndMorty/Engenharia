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
public class ListaClientes {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        //Cria os Clientes
        int cont = 0;
        int opcao = -1;
        int flag;
        Scanner entrada = new Scanner(System.in);

        
        //Cria a lista de Clientes
        List<Cliente> clientes = new ArrayList<>();
        List<Nacionalidade> nac = new ArrayList<>();
        
        //Adiciona os clientes na lista
        while (opcao != 0) {
            System.out.printf("Informe\n1 para inserir, \n2 para listar Clientes,\n3 para incluir Pais, \n4 para listar Paises cadastrados,\n0 para sair\n ");
            opcao = entrada.nextInt();
            Nacionalidade nacionalidade = new Nacionalidade("default", "default", "default");
            
            switch (opcao) {
            case 1:
                    Cliente cliente = new Cliente( "SemNome", "SemTelefone", "SemPais", 0, 0.00);
                    /*Não é permitido mais de um cliente com o mesmo nome;*/
                    flag = 0;


                    cliente.setNome();
                    for(int i = 0; i < clientes.size(); i ++){
                        if(clientes.get(i).getNome().equals(cliente.getNome()))
                        {
                            System.out.println("O nome ja consta na lista\n Por favor...");
                            cliente.setNome();
                            i = 0;
                        }
                    }
                    
                    cliente.setIdade();  
                    
                    //Inserindo pais
                    cliente.setPais();                   
                    cont =0;
                    if(!clientes.isEmpty()){
                        for(int i=0;i < clientes.size() ;i++)
                        {
                            if(nac.get(i).getPais().equals(cliente.getPais()))//estou comparando banco com o cadastro
                            {  
                            }else{cont++;}//verifica se não há nenhum pais com nome igual                    
                        }
                        if(cont == (clientes.size())){//se não tiver nome igual adiciona em nacionalidade
                            nacionalidade.setPais(cliente.getPais());
                            nacionalidade.setSigla();
                            nacionalidade.setCod_pais();
                            nac.add(nacionalidade);                        
                        }
                    }else{
                        nacionalidade.setPais(cliente.getPais());
                        nacionalidade.setSigla();
                        nacionalidade.setCod_pais();
                        nac.add(nacionalidade);
                        
                    }
                    do{//verifica se o telefone é valido
                        cliente.setTelefone();
                   
                    }while(cliente.getTelefone().toLowerCase().contains(nacionalidade.getCod_pais().toLowerCase()) == false);
                    clientes.add(cliente);
                break;

            case 2:
                if(clientes.isEmpty())
                {
                    System.out.println("Não há clientes cadastrados.");
                }
                else
                {
                    clientes.forEach((c) -> {
                    System.out.println("Cliente: " + c.getNome());
                    System.out.println("Telefone: " + c.getTelefone());
                    System.out.println("Pais: " + c.getPais());
                    System.out.println("Idade: " + c.getIdade());
                    System.out.println("Credito: " + c.getCredito());
                    });
                }
                break;
            case 3:
                System.out.println("Insira o Pais que deseja cadastrar");
                nacionalidade.setPais(entrada.next());
                nacionalidade.setSigla();
                nacionalidade.setCod_pais();
                if(!nac.isEmpty()){
                        for(int i=0;i < nac.size() ;i++)
                        {
                            if(nac.get(i).getPais().equals(nacionalidade.getPais()))//estou comparando banco com o cadastro
                            {                            
                                
                                //System.out.println("Pais ja cadastrado");
                                //cliente.setPais();
                                
                                // comparo o cadastro com o banco, se não estiver cadastrado eu cadastro.
                                //se ja estiver cadastrado não faço nada                                                                
                            
                            }else{cont++;}//verifica se não há nenhum pais com nome igual                    
                        }
                        if(cont == (nac.size())){//se não tiver nome igual adiciona em nacionalidade
                            //nacionalidade.setPais(cliente.getPais());
                            nac.add(nacionalidade);                        
                        }
                    }else{
                        //nacionalidade.setPais(cliente.getPais());
                        nac.add(nacionalidade);
                        
                    }break;
            case 4:
                if(clientes.isEmpty()){
                    System.out.println("Não há pais cadastrado");
                }else{
                    nac.forEach((c) -> {
                    System.out.println("Pais: " + c.getPais() + " - " + c.getSigla() + " codigo: " + c.getCod_pais());
                    });
                
                }break;
            case 0:
                System.out.println("bye");
            }

        }
        //Exibe os nomes dos clientes por um foreach      
    }
}
