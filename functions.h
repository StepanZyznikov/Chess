bool off_sound = false;
bool end_game;
int style = 1;
HDC bg_pic_cyberpunk;
HDC settings_pic_cyberpunk;
HDC bg_pic_classic;
HDC settings_pic_classic;
HDC field_pic;
HDC Black_marble;
HDC White_marble;
void write_file(string button_name);
void read_file();

void add_widgets();
void load_images();
void delete_images();
void menu();
void settings();
void on_sound_func();
void off_sound_func();
void classic_style_button_func();
void cyberpunk_style_button_func();
void start_game();
Button play_button(395, 243, start_game, "Играть", "Road Rage(RUS BY LYAJKA)", 70, 90, 355, RGB(247, 240, 1) , TX_BLACK, false);

Button settings_button(395, 348, settings, "Настройки", "Road Rage(RUS BY LYAJKA)", 70, 90, 355, RGB(247, 240, 1) , TX_BLACK, false); //76, 230, 119
Button on_sound_button(460, 395, on_sound_func, "Вкл", "Road Rage(RUS BY LYAJKA)", 70, 64, 108, RGB(76, 230, 119) , TX_BLACK, false);
Button off_sound_button(570, 395, off_sound_func, "Выкл", "Road Rage(RUS BY LYAJKA)", 70, 64, 115, RGB(230, 76, 76) , TX_BLACK, false);
Button classic_style_button(415, 570, classic_style_button_func, "Classic Style", "Road Rage(RUS BY LYAJKA)", 40, 85, 155, RGB(247, 240, 1) , TX_BLACK, false);
Button cyberpunk_style_button(575, 570, cyberpunk_style_button_func, "Cyberpunk Style", "Road Rage(RUS BY LYAJKA)", 30, 85, 158, RGB(247, 240, 1) , TX_BLACK, false);

Button back_button(415, 660, menu, "Назад", "Road Rage(RUS BY LYAJKA)", 70, 90, 318, RGB(247, 240, 1) , TX_BLACK, false);

void write_file(string button_name){
    //if(ifstream file("style_file.txt")){
    ofstream file("style_file.txt", ios_base::out);
    if(button_name == "classic_style_button"){
        file<< "classic";
        style = 2;
        for(auto button:buttons){
            button->set_bg_color(TX_BLUE);
        }
    }
    else if(button_name == "cyberpunk_style_button"){
        file<< "cyberpunk";
        style = 1;
        for(auto button:buttons){
            button->set_bg_color(RGB(247, 240, 1));
        }
    }
    file.close();
}

void read_file(){
    ifstream file;
    file>>style;
    file.close();
}

void add_widgets(){
    buttons.push_back(&play_button);
    buttons.push_back(&settings_button);
    buttons.push_back(&on_sound_button);
    buttons.push_back(&off_sound_button);
    buttons.push_back(&classic_style_button);
    buttons.push_back(&cyberpunk_style_button);
    buttons.push_back(&back_button);
}

void load_images(){
    bg_pic_cyberpunk = txLoadImage("Chess_menu1.bmp");
    settings_pic_cyberpunk = txLoadImage("Chess_settings_menu1.bmp");
    field_pic = txLoadImage("Chess_pic.bmp");
    bg_pic_classic = txLoadImage("Chess_menu2.bmp");
    settings_pic_classic = txLoadImage("Chess_settings_menu2.bmp");
    Black_marble = txLoadImage ("Black_marble.bmp");
    White_marble = txLoadImage ("White_marble.bmp");
}
void delete_images(){
    txDeleteDC(bg_pic_cyberpunk);
    txDeleteDC(field_pic);
    txDeleteDC(settings_pic_cyberpunk);
    txDeleteDC(Black_marble);
    txDeleteDC(White_marble);
}

void menu(){
    if(!off_sound){
        txPlaySound("bg_music.wav",SND_LOOP);
    }
    on_sound_button.set_state(false);
    off_sound_button.set_state(false);
    classic_style_button.set_state(false);
    cyberpunk_style_button.set_state(false);
    back_button.set_state(false);
    play_button.set_state(true);
    settings_button.set_state(true);
    if(style == 1){
        txBitBlt(txDC(),0,0,1200,800,bg_pic_cyberpunk,0,0);
    }
    else{
        txBitBlt(txDC(),0,0,1200,800,bg_pic_classic,0,0);
    }
}

void settings(){
    play_button.set_state(false);
    settings_button.set_state(false);
    on_sound_button.set_state(true);
    off_sound_button.set_state(true);
    classic_style_button.set_state(true);
    cyberpunk_style_button.set_state(true);
    back_button.set_state(true);
    if(style == 1){
        txBitBlt(txDC(),0,0,1200,800,settings_pic_cyberpunk,0,0);
    }
    else{
        txBitBlt(txDC(),0,0,1200,800,settings_pic_classic,0,0);
    }
}

void on_sound_func(){
    off_sound = false;
    txPlaySound("bg_music.wav",SND_ASYNC);
}

void off_sound_func(){
    off_sound = true;
    txPlaySound(NULL);
}

void classic_style_button_func(){
    write_file("classic_style_button");
}
void cyberpunk_style_button_func(){
    write_file("cyberpunk_style_button");
}

void start_game(){
    play_button.set_state(false);
    if(!field_pic){
        txMessageBox ("Не могу загрузить фон из Chess_pic.bmp");
    }
    ChessField field;
    txBegin();
    while(!GetAsyncKeyState(VK_ESCAPE)){
        //txSetFillColor(RGB(3, 171, 255));
        txClear();
        txBitBlt(txDC(),0,0,1200,800,field_pic,0,0);
        end_game = field.check_click();
        //field.pawn_to_queen();
        if(end_game){
            break;
        }
        //field.move_figure();

        field.draw();
        txSleep(10);
    }
    field.end(end_game);
    menu();
    //txDeleteDC(bg_pic);
    //txDeleteDC(field_pic);
}

