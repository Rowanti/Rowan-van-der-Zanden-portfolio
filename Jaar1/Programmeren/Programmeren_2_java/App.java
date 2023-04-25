public class App{
    public static void main(String[] args){
        LinkedList li = new LinkedList();
        Muppet animal = new Muppet("Animal", 9);
        Muppet beaker = new Muppet("Beaker", 4);
        Muppet gonzo = new Muppet("Gonzo", 21);
        Muppet kermit = new Muppet("Kermit", 1);
        Muppet missPiggy = new Muppet("Miss Piggy", 16);
        Muppet swedishChef = new Muppet("Swedish Chef", 7);
        li.pop(1);
        li.push(animal, 0);
        li.push(beaker, 1);
        li.push(gonzo, 2);
        li.push(kermit, 3);
        li.push(missPiggy, 4);
        li.push(swedishChef, 5);
        li.push(swedishChef, 5);
        li.print();
        li.push(li.pop("Swedish Chef"), 0);
        li.print();
    }
}