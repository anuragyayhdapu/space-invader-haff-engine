
Font font
{
 filename = font\font2.fnt
}

Sprite backgroundSprite1 
{
 texture = images\back1.jpg
 rect = 0, 0, 810, 470
}
Sprite backgroundSprite2
{
 texture = images\back2.jpg
 rect = 0, 0, 810, 470
}
Sprite machine_bullet_sprite
{
 texture = images\machine_bullet.png
 rect = 0, 0, 8, 25
}
Sprite plasma_bullet_sprite
{
 texture = images\plasma1.png
 rect = 0, 0, 13, 18
}
Sprite rocket_sprite
{
 texture = images\rocket2.png
 rect = 0, 0, 15, 46
}
Sprite plasma2_sprite
{
 texture = images\plasma2.png
 rect = 0, 0, 16, 17
}
Sprite enemy1_sprite
{
 texture = images\alien1.png
 rect = 0, 0, 60, 39
}
Sprite enemy2_sprite
{
 texture = images\alien2.png
 rect = 0, 0, 65, 50
}
Sprite enemy3_sprite
{
 texture = images\alien3.png
 rect = 0, 0, 127, 153
}
Sprite resource
{
 texture = images\resource.png
 rect = 0, 0, 28, 28
}
Sprite ammo
{
 texture = images\ammo.png
 rect = 0, 0, 43, 25
}
Sprite armour
{
 texture = images\armour.png
 rect = 0, 0, 31, 17
}
Sprite fuel
{
 texture = images\fuel.png
 rect = 0, 0, 18, 25
}


Animation a11_normalAnim
{
 texture = images\sc_sprite_normal.png
 rect = 0, 0, 34, 65
 frames = 4
 fps = 11.0
 mode = FORWARD,LOOP
}
Animation a11_blastoffAnim
{
 texture = images\sc_sprite_blastoff.png
 rect = 0, 0, 34, 83
 frames = 4
 fps = 11.0
 mode = FORWARD,LOOP
}
Animation blue_explosion
{
 texture = images\blue_explosion_sprite_sheet.png
 rect = 0, 0, 93, 93
 frames = 11
 fps = 15.0
 mode = FORWARD,LOOP
}
Animation rocket_explosion
{
 texture = images\rocket_explosion_sprite_sheet.png
 rect = 0, 0, 63, 54
 frames = 25
 fps = 15.0
 mode = FORWARD,LOOP
}
Animation rocket_anim
{
 texture = images\rocket_anim_sprite_sheet.png
 rect = 0, 0 , 16, 51
 frames = 2
 fps = 15.0
 mode = FORWARD,LOOP
}
Animation mine_animt
{
 texture = images\mine_anim_sprite_sheet.png
 rect 0, 0, 32, 16
 frames = 2
 fps = 8.0
 mode = FORWARD,LOOP
}
Animation fireball_anim
{
 texture = images\fireball_anim_sprite_sheet.png
 rect = 0, 0, 26, 32
 frames = 2
 fps = 15.0
 mode = FORWARD,LOOP
}
