package OneControlInterface.Model.View;/*
 *
 */

import OneControlInterface.Model.Model.Model;
import OneControlInterface.Model.Model.Value;

public class MenuItem {
    protected String caption;
    protected String valueID;
    protected String valueCaption;
    protected MenuItem next;
    protected MenuItem prev;
    protected MenuItem parent;
    protected Menu childMenu;
    protected Menu menu;

    public MenuItem(String caption) {
        this.caption = caption;
    }

    public MenuItem(String caption, String valueID, String valueCaption) {
        this(caption);
        this.valueID = valueID;
        this.valueCaption = valueCaption;
        next = this;
        prev = this;
        parent = this;
    }

    public MenuItem getNext() {
        return next;
    }

    public MenuItem getPrev() {
        return prev;
    }


    public MenuItem getParent() {
        return parent;
    }


    public Menu getChildMenu() {
        return childMenu;
    }

    public void setChildMenu(Menu childMenu) {
        this.childMenu = childMenu;
    }

    String getText() {
        return " caption:"+caption+ " name:"+valueCaption + " id:"+valueID;
    }

    public static void makeSiblings(MenuItem[] activities) {
        if (activities.length > 1) {
            int i = 1;
            do {
                activities[i-1].next = activities[i];
                activities[0].prev = activities[i];
                activities[i].next = activities[0];
                i++;
            } while (i < activities.length);

        }
    }

}