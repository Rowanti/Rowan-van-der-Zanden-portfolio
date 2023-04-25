/**
 * Herkansing einopdracht programmeren 3
 * Rowan van der Zanden - 1027332
 */

public class App {
    static int maxContainers = 10;
    public static void main(String[] args) {
        Containerschip schip = new Containerschip();
        Kade kade = new Kade();
        schip.generateContainers(maxContainers);
        Kraan[] kraanArray = {new Kraan(kade, schip, 1)
                            , new Kraan(kade, schip, 2)};
        Vrachtwagen[] vrachtwagenArray ={new Vrachtwagen(kade, "A")
                                        ,new Vrachtwagen(kade, "B")
                                        ,new Vrachtwagen(kade, "C")};
        for(Kraan k: kraanArray){
            k.start();
        }
        for(Vrachtwagen v: vrachtwagenArray){
            v.start();
        }
    }
}