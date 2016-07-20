package OneControlInterface.Model.View;

import OneControlInterface.Model.Model.Model;
import javafx.application.Application;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.Pane;
import javafx.stage.Stage;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by swanta on 02.07.16.
 */
public class View {//extends Application{

    private List<Menu> menus;
    private Menu rootMenu;
    private Menu currentMenu;
//    private MenuItem currentMenuItem;
    private int screenCharsInLine;
    private int screenLines;
    private Model model = new Model();

    public View(int screenLines, int screenCharsInLine, String menuConfig) {
        menus = new ArrayList<>();
        buildMenuTree(menuConfig);
        goRoot();
        this.screenLines = screenLines;
        this.screenCharsInLine = screenCharsInLine;
    }

    public void doEnter() {
        if (currentMenu.isValueEditor()) {
            goSaveMenu();
        } else {
            goChildMenu();
        }


    }

    public void doBack() {
        if (currentMenu.isValueEditor()) {
            goSaveMenu();
        } else {
            goParentMenu();
        }
    }

    public void doNext() {
        if (currentMenu.isValueEditor()) {
            model.increaseValue(currentMenu.currentItem.valueID);
        } else {
            goNextItem();
        }
    }

    public void doPrev() {
        if (currentMenu.isValueEditor()) {
            model.increaseValue(currentMenu.currentItem.valueID);
        } else {
            goPrevItem();
        }
    }

    public void doHome() {
        goRoot();
    }

    public void update() {
        System.out.println(currentMenu.getLines(screenLines));
    }

    private void buildMenuTree(String menuConfig) {
        String[] stringsConfig = menuConfig.split("\\|");
//        System.out.println(stringsConfig[1]);
        for (int i = 0; i < stringsConfig.length; i++) {
            String currentStringConfig = stringsConfig[i];
            System.out.println("found = string:"+currentStringConfig);
            String delim = currentStringConfig.substring(1, 2);
            System.out.println("delim:"+delim);
            String[] itemStrings = currentStringConfig.split(delim);
            String level = "";
            String caption  = "";
            String varCaption = "";
            String varID = "";
            if (itemStrings.length <2) {
                System.out.println("нет имени");
                continue;
            }
            if (itemStrings.length > 1) {
                level = itemStrings[0];
                caption = itemStrings[1];
            }
            if (itemStrings.length >2){
                varID = itemStrings[2];
            }
            if (itemStrings.length >3) {
                varCaption = itemStrings[2];
                varID = itemStrings[3];
            }
                MenuItem item = new MenuItem(caption, varCaption, varID);
            int itemLevel = Integer.valueOf(level);
            System.out.println("parsed = level:"+level+">"+itemLevel + " name:"+caption+ " var:"+varCaption + " id:"+varID);
            if (menus.isEmpty()) {
                    rootMenu = new Menu(itemLevel);
                    menus.add(rootMenu);
                    rootMenu.addItem(item);
                } else {
                    int prevMenuIndex = menus.size() - 1;
                    searchParentMenu:
                    for (int j = prevMenuIndex; j >= 0; j--) {
                        Menu prevMenu = menus.get(j);
                        if (prevMenu.getLevel() > itemLevel) {
                            prevMenu.addItem (item);
                            break searchParentMenu;
                        } else if (prevMenu.getLevel() <= itemLevel) {
                            makeChildMenu(prevMenu, item);
                            break searchParentMenu;
                        } else if (j == 0) {
//                        makes menu brother to root
//                        if can't find any siblings
                            rootMenu.addItem(item);
                        }
                    }

                }
                switch (delim) {
                    case ">":
                        MenuItem valueEditor = new MenuItem(caption, varID, varCaption);
                        makeChildMenu(getLastMenu(), valueEditor);
                        Menu valueEditorMenu = getLastMenu();
                        buildValueSaveMenu(valueEditorMenu);
                        Menu valueSaveMenu = getLastMenu();
                        valueEditorMenu.parentMenuItem.menu = valueSaveMenu;
                        valueEditorMenu.setValueEditor();
                        break;
                }


        }
    }

    private void buildValueSaveMenu(Menu editorMenu) {
        MenuItem save = new MenuItem("Сохранить");
        makeChildMenu(editorMenu, save);
        Menu saveMenu = getLastMenu();
        MenuItem back = new MenuItem("Править");
        MenuItem cancel = new MenuItem("Вернуть");
        saveMenu.addItem(back);
        saveMenu.addItem(cancel);
        save.childMenu = editorMenu.parentMenuItem.menu;
        cancel.childMenu = editorMenu.parentMenuItem.menu;
        back.childMenu = editorMenu;
    }

    private Menu getLastMenu() {
        return menus.get(menus.size() - 1);
    }


    private void makeChildMenu(Menu prevMenu, MenuItem item) {
        MenuItem parentItem = prevMenu.items.get(0).prev;
        Menu newMenu = new Menu(prevMenu.getLevel()+1);
        menus.add(newMenu);
        parentItem.childMenu = newMenu;
        newMenu.addItem(item);
    }

    private void goSaveMenu() {
        goChildMenu();
    }

    private void goChildMenu() {
        gotoMenu(currentMenu.currentItem.childMenu);
    }

    private void goParentMenu() {
        gotoMenu(currentMenu.parentMenuItem.menu);

    }


    private void goNextItem() {
        gotoMenuItem(currentMenu.currentItem.next);
    }

    private void goPrevItem() {
        gotoMenuItem(currentMenu.currentItem.prev);
    }

    private void gotoMenuItem(MenuItem item) {
        currentMenu.currentItem = item;
    }

    private void goRoot() {
        gotoMenu(rootMenu);
    }

    private void gotoMenu(Menu menu) {
        gotoMenu(menu, false);
    }
    private void gotoMenu(Menu menu, boolean dontSaveMenuPosition) {
        if (dontSaveMenuPosition) currentMenu.currentItem = currentMenu.items.get(0);
        currentMenu = menu;
    }

     public Model getModel() {
        return model;
    }

//    private Label textOut = new Label();

//    @Override
//    public void start(Stage primaryStage) throws Exception {
//        primaryStage.setTitle("LCD+encoder");
//        BorderPane root = new BorderPane();
//        Scene scene = new Scene(root, 300, 200);
//        primaryStage.setScene(scene);
//
//        root.setCenter(textOut);
//    }
}
