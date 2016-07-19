package OneControlInterface.Model;

import java.util.Random;

public  class Value <T extends Number>{
    protected String caption;
    protected T value;
//    public float step;
    private boolean isUserModifiable;

    public Value(String caption, T value) {
        System.out.println("создаю объект под "+caption);
        isUserModifiable = false;
        this.caption = caption;
        this.value = value;
    }




    String getTextLine() {
        return getTextLine(value);
    }
    String getTextLine(T value) {
        return caption + ":" + value;
    }

    T getValue() {
        return value;
    }

    String getCaption() {
        return caption;
    }

    public static float random(float base){
        Random random = new Random();
        return base + random.nextFloat()*2-1;
    }
    public static int random(int bound){
        Random random = new Random();
        return random.nextInt(bound);
    }
//    void randomize(){
//        value = Value.random(2f);
//    }
    public void saveNewValue(){}

}
