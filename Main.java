import java.io.File;
import java.util.*;

class Processus {

    private String nom;
    private int temps_arr;
    private int temps_exe;

    public Processus(String nom, int temps_arr, int temps_exe) {
        this.nom = nom;
        this.temps_arr = temps_arr;
        this.temps_exe = temps_exe;
    }

    public String getNom() {
        return nom;
    }

    public int getTemps_arr() {
        return temps_arr;
    }

    public int getTemps_exe() {
        return temps_exe;
    }

    public void setNom(String nom) {
        this.nom = nom;
    }

    public void setTemps_arr(int temps_arr) {
        this.temps_arr = temps_arr;
    }

    public void setTemps_exe(int temps_exe) {
        this.temps_exe = temps_exe;
    }
}



class  The_Comparator implements Comparator<Processus> {



    @Override
    public int compare(Processus p1, Processus p2) {
        return p1.getTemps_arr()-p2.getTemps_arr();
    }
}



public class Main {

    public static void main(String args[])  {
        List<Processus> procs1 = getprocessus();
        System.out.println("Voici la liste de processus :");
        for (Processus p : procs1){
            System.out.println(p.getNom()+"   "+p.getTemps_arr()+"  "+p.getTemps_exe());
        }
        boolean boucle = true;
        while (boucle) {
            System.out.println("---------------------------------------------------");
            List<Processus> procs = getprocessus();
            System.out.println();
            System.out.print("Choisissez le type d'ordonnancement (FIFO, SJF, RR) : ");
            Scanner scanner = new Scanner(System.in);
            String inputString = scanner.nextLine();
            switch (inputString) {
                case "FIFO":
                    fifo(procs);
                    System.out.println();
                    break;
                case "SJF":
                    sjf(procs);
                    System.out.println();
                    break;
                case "RR":
                    rr(procs);
                    System.out.println();
                    break;
                case "BYE":boucle=false;
                    System.out.println("CIAOOOO!");
                    break;
                default:
                    System.out.println("again !!!");
            }
        }


    }

    public static void rr(List<Processus> procs) {
        Collections.sort(procs, new Comparator<Processus>() {
            @Override
            public int compare(Processus p1, Processus p2) {
                return p1.getTemps_arr()-p2.getTemps_arr();
            }
        });

        int qun = 3;
        int i=0;
        int sq=0;
	System.out.println("Quantum choisi : 3");
        while(!procs.isEmpty()){
            Processus p = procs.get(sq);

            if(p.getTemps_arr()<=i){
                if(p.getTemps_exe()<=3){
                    procs.remove(p);

                    System.out.println(p.getNom()+" execute un quantum et termine son execution");
                    i+=p.getTemps_exe();

                }
                else{
                    p.setTemps_exe(p.getTemps_exe()-qun);
                    i+=qun;
                    System.out.println(p.getNom()+" execute un quantum et lui reste "+p.getTemps_exe()+" unites");
                    sq++;
                }

            }

            if(sq==procs.size())sq=0;

        }

    }

    public static void sjf(List<Processus> procs) {

        Collections.sort(procs, new Comparator<Processus>() {
            @Override
            public int compare(Processus p1, Processus p2) {
                return p1.getTemps_exe()-p2.getTemps_exe();
            }


        });
        int i =0;
        while(!procs.isEmpty()){

            for(Processus p :procs){
                if(p.getTemps_arr()<=i) {
                    procs.remove(p);
                    i += p.getTemps_exe();
                    System.out.println(p.getNom() + " est en cours d'execution ");
                    break;
                }
            }

        }

    }

    public static void fifo(List<Processus> procs) {
        PriorityQueue<Processus> processuses=new PriorityQueue<Processus>(new The_Comparator());
        processuses.addAll(procs);
        System.out.println("Proc    Temps d'arrivee     Temps d'execution ");
        while(!processuses.isEmpty())
        {
            Processus p= processuses.remove();

            System.out.println(p.getNom() + "           "+p.getTemps_arr()+"                  "+p.getTemps_exe());
        }
    }




    public static List<Processus> getprocessus(){

        File file =   new File("/home/bahreee/Desktop/processus1.txt");
        List<Processus>prs = new ArrayList<>();
        try (Scanner sc = new Scanner(file)) {

            while (sc.hasNextLine()){

                String str= sc.nextLine();
                String[] splits = str.split(" ");
                Processus p = new Processus(splits[0],Integer.parseInt(splits[1]),Integer.parseInt(splits[2]));
                prs.add(p);
            }

        }
        catch(Exception e){
            System.out.println(e.fillInStackTrace());
        }
        return prs;
    }
}
