package OneControlInterface.Model.View;

import java.util.ArrayList;
import java.util.List;

public class Menu {
    private final int level;
    //private LiquidScreen lcdScreen;
    List<MenuItem> items = new ArrayList<>();
    MenuItem currentItem;
//    Menu parentMenu;
    MenuItem parentMenuItem;

    public void setValueEditor() {
        this.valueEditor = true;
    }

    private boolean valueEditor;

    public Menu( int level) {
        this.level = level;
        System.out.println(level + " - новое меню");
    }
    public Menu( int level, MenuItem parentMenuItem) {
        this(level);
        this.parentMenuItem = parentMenuItem;
        parentMenuItem.setChildMenu(this);
    }

    public String getLine() {
        String string;
        if (currentItem == null) {
            string = "LineTextInterface.View.MenuItem not loaded";
        } else {
            string = " level:"+level+ "\n>>" + currentItem.getText();
        }
        return string;
    }

    String[] getLines(int linesCount) {
        int linesShown = Math.min(linesCount, items.size());
        String[] strings = new String[linesShown];
        if (linesCount == 1) {
            strings[0] = getLine();
        } else if (linesCount > 1) {
            for (int i = 0; i < linesShown; i++) {
                strings[i] = items.get(i).getText();
            }
        }
        return strings;
    }


    private Menu goParentMenu() {
        exitMenu();
        return parentMenuItem.getChildMenu();
    }

    private Menu enterMenu() {
        currentItem = items.get(0);
        return this;
    }

    protected void exitMenu() {
        currentItem = items.get(0);
    }

    protected void addItem(MenuItem item) {
        if (parentMenuItem != null) {
            System.out.println("добавляю в меню " + this.parentMenuItem.caption + " пункт " + item.caption);
        } else {
            this.parentMenuItem = item;
            System.out.println("добавляю в главное меню пункт " + item.caption);
        }
        if (items.add(item)) {
            item.next = items.get(0);
            item.prev = items.get(0).prev;
            items.get(0).prev = item;
            item.menu = this;
            if (currentItem == null) {
                currentItem = item;
                System.out.println(" = сделан главным пунктом");
            }
        } else System.out.println(" = не добавился");
    }

    protected int getLevel() {
        return level;
    }

    public boolean isValueEditor() {
        return valueEditor;
    }
}
