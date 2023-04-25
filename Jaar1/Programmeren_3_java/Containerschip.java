/**
 * Herkansing einopdracht programmeren 3
 * Rowan van der Zanden - 1027332
 */
import java.util.ArrayList;
import java.util.Random;

public class Containerschip {
    public int containerCount;
    public ArrayList<Container> schipList = new ArrayList<Container>();
    public void generateContainers(int maxContainers){
        for(int i = 0;i < maxContainers; i++){
            Random r = new Random();
            Container container = new Container(i, r.nextInt(3));
            schipList.add(container);
        }
        containerCount = schipList.size();
    }
}
