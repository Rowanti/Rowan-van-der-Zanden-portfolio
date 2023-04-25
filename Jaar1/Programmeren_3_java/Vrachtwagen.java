/**
 * Herkansing einopdracht programmeren 3
 * Rowan van der Zanden - 1027332
 */
import java.util.Random;
public class Vrachtwagen extends Thread{
    public Kade kade;
    public String id;
    public Container container;
    Vrachtwagen(Kade kade, String id){
        this.kade = kade;
        this.id = id;
    }
    public void run(){
        pakVanKade();
    }
    public void pakVanKade(){
        while(kade.vrachtwagenCount > 0){
            while(!kade.kadeList.isEmpty()){
                try{
                this.container = kade.kadeList.get(kade.kadeList.size()-1);
                kade.kadeList.remove(kade.kadeList.size()-1);
                printLaden();
                wachtTijd();
                printLossen();
                this.container = null;
                kade.vrachtwagenCount--;
                } catch (IndexOutOfBoundsException e){
                } catch (Exception e){
                }
            }
            synchronized(kade){
                try {
                    notifyAll();
                    wait();
                } catch (InterruptedException e) {
                } catch (Exception e){
                }
            }
        }
    }
    public void printLaden(){
        if(container.type == 1){
            System.out.println("container: " + container.id +" wordt gekoppeld aan de verwarmingselementen");
        } else if (container.type == 2){
            System.out.println("container: " + container.id +" wordt gekoppeld aan de koelingselementen");
        }
        System.out.println("vrachtwagen: " + this.id + " laadt container: " 
        + container.id);
    }
    public void printLossen(){
        System.out.println("Vrachtwagen: " + this.id + " heeft container: "
        + container.id + " weggebracht");
    }
    public void wachtTijd() {
        Random r = new Random();
        try {
            Thread.sleep(r.nextInt(5000) + 1000);
        } catch (InterruptedException e) {
        }
    }
}
