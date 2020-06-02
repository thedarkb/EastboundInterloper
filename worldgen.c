void generateTunnels() {
	for(int i=0; i<TLIMIT/2; i++) {
		duplicate://Dirty, I know.
		reroll();
		tunnels[i].m=(rng.uc%2)*-1;
		reroll();
		tunnels[i].c=(rng.ui32%550)>>1;
		tunnels[i].c<<=1;

		for(int j=0; j<i; j++) if(tunnels[i].m == tunnels[j].m && tunnels[i].c == tunnels[j].c) goto duplicate;
		//Goes back to the top of the for loop if a duplicate line is detected.
		printf("Tunnel %d, m=%d; c=%d\n", i, tunnels[i].m, tunnels[i].c);
		//printf("%d,%d\n", i, tunnels[i].m, tunnels[i].c);
	}
	for(int i=TLIMIT/2; i<TLIMIT; i++) {
		duplicate1://Dirty, I know.
		reroll();
		tunnels[i].m=rng.uc%2;
		reroll();
		tunnels[i].c=((rng.ui32%550)*-1)>>1;
		tunnels[i].c<<=1;

		for(int j=0; j<i; j++) if(tunnels[i].m == tunnels[j].m && tunnels[i].c == tunnels[j].c) goto duplicate1;
		//Goes back to the top of the for loop if a duplicate line is detected.
		printf("Tunnel %d, m=%d; c=%d\n", i, tunnels[i].m, tunnels[i].c);
		//printf("%d,%d\n", i, tunnels[i].m, tunnels[i].c);
	}
	tunnels[0].m=0;
	tunnels[0].c=300;
}

void axiomLoad(){
	memset(mapLoader,0,sizeof mapLoader);
	view inMap;
	FILE* inFile=NULL;
	if(!(inFile=fopen(WORLDFILENAME, "rb"))) {
		printf(WORLDFILENAME);
		printf(" not found, exiting.\n");
		exit(1);
	}
	while(fread(&inMap, sizeof inMap, 1, inFile)) {
		printf("Map segment found with sX:%u and sY:%u.\n", inMap.sX, inMap.sY);
		mapLoader[inMap.sX][inMap.sY]=malloc(sizeof inMap);
		*mapLoader[inMap.sX][inMap.sY]=inMap;
	}
}

void entFetch(unsigned int xIn, unsigned int yIn) {
	uint32_t screenNum=0;
	screenNum |= sX+(xIn-1);
	screenNum |= sY+(yIn-1) << 16;
	
	int xMult=(xIn-1)*(SW*TS);
	int yMult=(yIn-1)*(SH*TS);
	int xOffset=(xIn-1);
	int yOffset=(yIn-1);

	printf("EntFetch entered...\n");

	for(int i=0;i<MAPELIMIT;i++) {
		if(!tilewrapper[xIn][yIn].preSpawns[i].id) continue;
		printf("Entity found, spawning at %u,%u\n",tilewrapper[xIn][yIn].sX,tilewrapper[xIn][yIn].sY);
		mapEntitySpawn(topLevelEntities[tilewrapper[xIn][yIn].preSpawns[i].id](
			tilewrapper[xIn][yIn].preSpawns[i].a1,
			tilewrapper[xIn][yIn].preSpawns[i].a2,
			tilewrapper[xIn][yIn].preSpawns[i].a3,
			tilewrapper[xIn][yIn].preSpawns[i].a4),
			tilewrapper[xIn][yIn].sX,
			tilewrapper[xIn][yIn].sY,
			tilewrapper[xIn][yIn].preSpawns[i].x,
			tilewrapper[xIn][yIn].preSpawns[i].y);
	}

	tilewrapper[xIn][yIn].flag=0;
}

void loadSpawn() {
	for(int x=0; x<3; x++) {
		for(int y=0; y<3; y++) {
			if (tilewrapper[x][y].flag) {
				entFetch(x,y);
				//factionFetch(x,y);
				tilewrapper[x][y].flag=0;
			}
		}
	}
}

void worldgen(view* in, uint16_t xPos, uint16_t yPos) {
	loadSpawn();
	uint32_t screenHash=PAIR(xPos,yPos);
	screenHash = lfsr(screenHash);
	memset(in,0,sizeof tilewrapper[1][1]);

	#ifdef DEV
	if(editorArray[xPos][yPos]) {
		*in=*editorArray[xPos][yPos];
		in->flag=1;
		return;
	}
	#endif

	//memset(in,0,sizeof *in);
	//return;

	if(mapLoader[xPos][yPos]) {
		*in=*mapLoader[xPos][yPos];
		in->flag=1;
		return;
	}
	//memset(in,0,sizeof tilewrapper[1][1]);
	//return;

	//printf("Difference: %d\n", diff);
	if(DIST(xPos,yPos,400,400)<40000 && yPos>250 && xPos<267) {
		*in=map_grasslandBase(xPos,yPos);
	} else if( DIST(xPos,yPos,400,400)<40000 && yPos<250){
		*in=map_snowlandBase(xPos,yPos);
	} else if(DIST(xPos,yPos,400,400)<40000 && yPos==250) {
		*in=map_snowgrass(xPos,yPos);
	} else if((DIST(xPos,yPos,400,400)<40000 && yPos>250 && xPos>267)) {
		*in=map_burren(xPos,yPos);
	} else if (DIST(xPos,yPos,400,400)<40804){
		*in=map_beach(xPos,yPos);
	} else if(xPos<605&&yPos<605){
		memset(&in->screen,21,sizeof in->screen);
		memset(&in->layers,1,sizeof in->layers);
	} else if(xPos<600 && yPos>600) {
		for(int i=0;i<TLIMIT;i++){
			if(yPos-600==(xPos*tunnels[i].m)+tunnels[i].c && tunnels[i].c ||
				yPos-600==((xPos-1)*tunnels[i].m)+tunnels[i].c && tunnels[i].c) {
				memset(in,0,sizeof(view));
				memset(in->screen,1,sizeof in->screen);
			}
		}
	} else {
		memset(in,0,sizeof tilewrapper[1][1]);
	}
	memset(in->preSpawns,0,sizeof(in->preSpawns));
	in->flag=0;
}

void scrollMap() {
	int checkX = entSet[0].x;
	int checkY = entSet[0].y;
	//collisionReset=1;
	const int speed=(TS*SW)/24;
	switch (scroll) {
		case 1:
			entityScroll(0,1);
			
			checkY=TS*SH-5;
			sY--;

			for(int i=0;i<3;i++) tilewrapper[i][2]=tilewrapper[i][1];
			for(int i=0;i<3;i++) tilewrapper[i][1]=tilewrapper[i][0];
			
			worldgen(&tilewrapper[0][0],sX-1,sY-1);			
			worldgen(&tilewrapper[1][0],sX,sY-1);			
			worldgen(&tilewrapper[2][0],sX+1,sY-1);
			
			cameraX=entSet[0].x;
			cameraY=entSet[0].y;
		scroll=0;
		break;
		case 2:
		checkY=5;
			entityScroll(0,-1);
			sY++;
			
			
			tilewrapper[0][0]=tilewrapper[0][1];
			tilewrapper[1][0]=tilewrapper[1][1];
			tilewrapper[2][0]=tilewrapper[2][1];
			
			tilewrapper[0][1]=tilewrapper[0][2];
			tilewrapper[1][1]=tilewrapper[1][2];
			tilewrapper[2][1]=tilewrapper[2][2];
			
			worldgen(&tilewrapper[0][2],sX-1,sY+1);
			worldgen(&tilewrapper[1][2],sX,sY+1);
			worldgen(&tilewrapper[2][2],sX+1,sY+1);

			
			//entSet[0].x=checkX;
			//entSet[0].y=1;
			cameraX=entSet[0].x;
			cameraY=entSet[0].y;
			scroll=0;
		break;
		case 3:
			entityScroll(1,0);
			sX--;
			
			tilewrapper[2][0]=tilewrapper[1][0];
			tilewrapper[2][1]=tilewrapper[1][1];
			tilewrapper[2][2]=tilewrapper[1][2];
			
			tilewrapper[1][0]=tilewrapper[0][0];
			tilewrapper[1][1]=tilewrapper[0][1];
			tilewrapper[1][2]=tilewrapper[0][2];

			worldgen(&tilewrapper[0][0],sX-1,sY-1);
			worldgen(&tilewrapper[0][1],sX-1,sY);	
			worldgen(&tilewrapper[0][2],sX-1,sY+1);
			
			//entSet[0].x=TS*SW-TS;
			cameraX=entSet[0].x;
			cameraY=entSet[0].y;
			scroll=0;
		break;
		case 4:
			entityScroll(-1,0);
			sX++;
			
			tilewrapper[0][0]=tilewrapper[1][0];
			tilewrapper[0][1]=tilewrapper[1][1];
			tilewrapper[0][2]=tilewrapper[1][2];
			
			tilewrapper[1][0]=tilewrapper[2][0];
			tilewrapper[1][1]=tilewrapper[2][1];
			tilewrapper[1][2]=tilewrapper[2][2];

			worldgen(&tilewrapper[2][0],sX+1,sY-1);
			worldgen(&tilewrapper[2][1],sX+1,sY);
			worldgen(&tilewrapper[2][2],sX+1,sY+1);
			
			//entSet[0].x=-TS+1;
			cameraX=entSet[0].x;
			cameraY=entSet[0].y;
			scroll=0;
		break;			
	}
}

