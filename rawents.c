//These are all sloppily set up entities from a distant early phase in development before I decided to use an entity ID system.
//If I had what this became in mind when I started this tech demo in December, none of this filth would be here.

entity ent_playerM() { //Male
	entity me;
	memset(&me, 0, sizeof me);
	me.behaviour=playerBehaviour;
	me.x=112;
	me.y=64;
	me.layer=2;
	me.health=pMaxHealth;
	me.attack=5;
	me.xSub=TS/5;
	me.ySub=1;
	me.direction=1;
	me.visible=1;
	me.collisionClass=1;
	me.frame[0]=148; //up
	me.frame[1]=124; //down
	me.frame[2]=132; //left
	me.frame[3]=140; //right
	me.frame[4]=147; //up step1
	me.frame[5]=123; //down step1
	me.frame[6]=131; //left step1
	me.frame[7]=139; //right step1
	me.frame[8]=149; //up step2
	me.frame[9]=125; //down step2
	me.frame[10]=133; //left step2
	me.frame[11]=141; //right step2
	return me;
}

entity ent_sword(int direction, int x, int y, int creator) {
	entity me;
	entSet[creator].freezeFrames=5;
	memset(&me, 0, sizeof me);
	switch(direction){
		case UP:
			me.y-=TS;
			me.xSub=TS/2;
			me.ySub=TS/2;
			//me.hitY+=5;
		break;
		case DOWN:
			me.y+=TS;
			me.xSub=TS/2;
			me.ySub=TS/2;
			//me.hitY-=5;			
		break;
		case LEFT:
			me.x-=TS;
			me.xSub=TS/2;
			me.ySub=TS/2;
			//me.hitX+=5;
		break;
		case RIGHT:
			me.x+=TS;
			me.xSub=TS/2;
			me.ySub=TS/2;
			//me.hitX-=5;
		break;
	}
	me.radius=5;
	me.frame[0]=92;
	me.frame[1]=101;
	me.frame[2]=90;
	me.frame[3]=89;
	me.frame[4]=100;
	me.frame[5]=93;
	me.frame[6]=91;
	me.frame[7]=88;
	me.health=255;
	me.lastHit=255;
	me.collider=col_weapon;
	me.layer=2;
	me.visible=0;
	me.status[0]=10;
	me.status[1]=creator;
	me.behaviour=behav_sword;
	me.setframe=direction;
	me.collisionClass=129;
	return me;
}

entity ent_axe(int direction, int x, int y, int creator) {
	entity me;
	entSet[creator].freezeFrames=10;
	memset(&me, 0, sizeof me);
	switch(direction){
		case UP:
			me.y-=TS;
			me.xSub=TS/2;
			me.ySub=TS/2;
			//me.hitY+=7;
		break;
		case DOWN:
			me.y+=TS;
			me.xSub=TS/2;
			me.ySub=TS/2;
			//me.hitY-=7;			
		break;
		case LEFT:
			me.x-=TS;
			me.xSub=TS/2;
			me.ySub=TS/2;
			//me.hitX+=7;
		break;
		case RIGHT:
			me.x+=TS;
			me.xSub=TS/2;
			me.ySub=TS/2;
			//me.hitX-=7;
		break;
	}
	me.radius=5;
	me.frame[0]=108;
	me.frame[1]=117;
	me.frame[2]=106;
	me.frame[3]=105;
	me.frame[4]=116;
	me.frame[5]=109;
	me.frame[6]=107;
	me.frame[7]=104;
	me.health=255;
	me.lastHit=255;
	me.collider=col_weapon;
	me.layer=2;
	me.visible=0;
	me.status[0]=10;
	me.status[1]=creator;
	me.behaviour=behav_sword;
	me.setframe=direction;
	me.collisionClass=129;
	return me;
}

entity ent_staff(int direction, int x, int y, int creator) {
	entity me;
	entSet[creator].freezeFrames=1;
	memset(&me, 0, sizeof me);
	switch(direction){
		case 0:
			me.y-=TS;
			me.xSub=TS/2;
			me.ySub=TS/2;
			//me.hitY+=7;
		break;
		case 1:
			me.y+=TS;
			me.xSub=TS/2;
			me.ySub=TS/2;
			//me.hitY-=7;			
		break;
		case 2:
			me.x-=TS;
			me.xSub=TS/2;
			me.ySub=TS/2;
			//me.hitX+=7;
		break;
		case 3:
			me.x+=TS;
			me.xSub=TS/2;
			me.ySub=TS/2;
			//me.hitX-=7;
		break;
	}
	me.radius=5;
	me.frame[0]=108;
	me.frame[1]=117;
	me.frame[2]=106;
	me.frame[3]=105;
	me.frame[4]=116;
	me.frame[5]=109;
	me.frame[6]=107;
	me.frame[7]=104;
	me.health=255;
	me.lastHit=255;
	me.collider=col_weapon;
	me.layer=2;
	me.visible=0;
	me.status[0]=10;
	me.status[1]=creator;
	me.behaviour=behav_sword;
	me.setframe=direction;
	me.collisionClass=129;
	return me;
}

entity ent_dialogue(int direction, int x, int y, int filler) {
	entity me;
	memset(&me, 0, sizeof me);
	switch(direction){
		case 0:
			me.y-=TS;
			me.xSub=TS/2;
			me.ySub=TS/2;
			//me.hitY+=5;
		break;
		case 1:
			me.y+=TS;
			me.xSub=TS/2;
			me.ySub=TS/2;
			//me.hitY-=5;			
		break;
		case 2:
			me.x-=TS;
			me.xSub=TS/2;
			me.ySub=TS/2;
			//me.hitX+=5;
		break;
		case 3:
			me.x+=TS;
			me.xSub=TS/2;
			me.ySub=TS/2;
			//me.hitX-=5;
		break;
	}
	me.radius=5;
	me.frame[0]=67;
	me.frame[1]=67;
	me.frame[2]=67;
	me.frame[3]=67;
	me.layer=1;
	me.health=255;
	me.lastHit=255;
	me.status[0]=10;
	me.status[1]=0;
	me.behaviour=behav_dialogue;
	me.collider=col_dialogue;
	me.setframe=direction;
	me.visible=0;
	me.collisionClass=131;
	return me;
}

entity ent_wall(int tile, int lol1, int lol2, int lol3) {
	entity me;
	memset(&me,0,sizeof me);
	me.behaviour=behav_wall;
	me.health=1;
	me.layer=0;
	me.frame[0]=tile;
	me.setframe=0;
	return me;
}

entity ent_nonsolid(int x, int y, int tile, int filler) {
	entity me;
	me.behaviour=behav_potato;
	me.collisionClass=0;
	me.health=1;
	me.x=x*TS;
	me.y=y*TS;
	me.layer=0;
	me.animation=0;
	me.direction=0;
	me.frame[0]=tile;
	me.setframe=0;
	return me;
}

entity ent_techNpc(int lol1, int lol2, int lol3, int lol4) {
	entity me;
	printf("Spawning tech NPC\n");
	memset(&me, 0, sizeof me);
	me.collisionClass=2;
	me.xSub=2;
	me.ySub=10;
	me.visible=1;
	me.frame[0]=145;
	me.frame[1]=121;
	me.frame[2]=129;
	me.frame[3]=137;
	me.frame[4]=144;
	me.frame[5]=120;
	me.frame[6]=128;
	me.frame[7]=136;
	me.frame[8]=146;
	me.frame[9]=122;
	me.frame[10]=130;
	me.frame[11]=138;
	me.clothes=cloth_default();
	me.health=20;
	me.layer=1;
	me.behaviour=behav_npcSpawn;
	return me;	
}

entity ent_agNpc(int lol1, int lol2, int lol3, int lol4) {
	entity me;
	printf("Spawning AG NPC\n");
	memset(&me, 0, sizeof me);
	me.collisionClass=2;
	me.xSub=2;
	me.ySub=10;
	me.visible=1;
	me.frame[0]=145;
	me.frame[1]=121;
	me.frame[2]=129;
	me.frame[3]=137;
	me.frame[4]=144;
	me.frame[5]=120;
	me.frame[6]=128;
	me.frame[7]=136;
	me.frame[8]=146;
	me.frame[9]=122;
	me.frame[10]=130;
	me.frame[11]=138;
	me.clothes=cloth_default();
	me.health=20;
	me.layer=1;
	me.dialogue=diag_civilWar;
	me.behaviour=behav_npcSpawn;
	return me;	
}

entity ent_npc(int lol1, int lol2, int lol3, int lol4) {
	entity me;
	printf("Spawning NPC\n");
	memset(&me,0,sizeof me);
	me.frame[0]=153;
	/*me.frame[0]=177;
	me.frame[1]=153;
	me.frame[2]=161;
	me.frame[3]=169;
	me.frame[4]=176;
	me.frame[5]=152;
	me.frame[6]=160;
	me.frame[7]=168;
	me.frame[8]=178;
	me.frame[9]=154;
	me.frame[10]=162;
	me.frame[11]=170;*/
	me.layer=1;
	me.visible=1;
	me.health=255;
	me.collisionClass=2;
	me.behaviour=behav_wall;
	me.dialogue=diag_menuTest;
	me.collider=col_bouncy;
	return me;
}

entity ent_door(int tile, int destSx, unsigned int destSy, int destX, int destY) {
	entity me;
	memset(&me,0,sizeof me);
	me.collisionClass=132;
	me.health=255;
	me.frame[0]=tile;
	me.status[0]=destSx;
	me.status[1]=destSy;
	me.status[2]=destX;
	me.status[3]=destY;
	me.xSub=10;
	me.ySub=10;
	me.behaviour=behav_door;
	return me;
}

entity ent_empty() {
	entity me;
	memset(&me,0,sizeof me);
	return me;
}
