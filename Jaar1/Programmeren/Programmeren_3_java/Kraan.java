/**
 * Herkansing einopdracht programmeren 3
 * Rowan van der Zanden - 1027332
 */
import java.util.Random;
public class Kraan extends Thread{
    public Containerschip schip = new Containerschip();
    public Container container;
    public Kade kade;
    public int id;
    Kraan(Kade kade, Containerschip schip, int id){
        this.kade = kade;
        this.schip = schip;
        this.id = id;
    }
    public void run(){
        verplaatsNaarKade();
    }
    public void verplaatsNaarKade(){
        while(schip.containerCount > 0){
            if (kade.kadeList.size() < 5){
                try{
                this.container = schip.schipList.get(0);
                schip.schipList.remove(0);
                printOppakken();
                verplaatsTijd();
                kade.kadeList.add(this.container);
                printNeerzetten();
                schip.containerCount--;
                this.container = null;
                } catch (IndexOutOfBoundsException e){
                } catch (Exception e){
                }
            }
            synchronized(schip){
                try {
                    notifyAll();
                    wait();
                } catch (InterruptedException e) {
                } catch (Exception e){
                }
            }
        }
        System.out.println("done");
    }
    public void printOppakken(){
        if(container.type == 1){
            System.out.println("container: " + container.id +" wordt losgekoppeld uit de verwarmingselementen");
        } else if (container.type == 2){
            System.out.println("container: " + container.id +" wordt losgekoppeld uit de koelingselementen");
        }
        System.out.println("kraan: " + id + " pakt container: " 
        + container.id + " van het containerschip");
    }
    public void printNeerzetten(){
        System.out.println("kraan: " + id + " zet container: " 
        + container.id + " op de kade");
    }
    public void verplaatsTijd(){
        Random r = new Random();
        try {
            Thread.sleep(r.nextInt(5000) + 1000);
        } catch (InterruptedException e) {
        } catch (Exception e){

        }
    }
}