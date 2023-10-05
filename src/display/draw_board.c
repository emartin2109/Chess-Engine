#include "include.h"
#include "define.h"
#include "display.h"
#include "global.h"

// global variable needed for this shitty library
GLuint pieceTextures[2][6];


void enableAlphaBlending() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

GLuint loadTexture(const char* filename) {
    GLuint texture = SOIL_load_OGL_texture(
        filename,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    if (!texture) {
        printf("Error loading texture: %s\n", SOIL_last_result());
    }
    return texture;
}

void initializeTextures() {
    // Load textures for white and black pieces (example filenames)
    pieceTextures[0][0] = loadTexture("assets/white_rook.png");
    pieceTextures[0][1] = loadTexture("assets/white_knight.png");
    pieceTextures[0][2] = loadTexture("assets/white_bishop.png");
    pieceTextures[0][3] = loadTexture("assets/white_queen.png");
    pieceTextures[0][4] = loadTexture("assets/white_king.png");
    pieceTextures[0][5] = loadTexture("assets/white_pawn.png");

    pieceTextures[1][0] = loadTexture("assets/black_rook.png");
    pieceTextures[1][1] = loadTexture("assets/black_knight.png");
    pieceTextures[1][2] = loadTexture("assets/black_bishop.png");
    pieceTextures[1][3] = loadTexture("assets/black_queen.png");
    pieceTextures[1][4] = loadTexture("assets/black_king.png");
    pieceTextures[1][5] = loadTexture("assets/black_pawn.png");
}

void drawPiece(int pieceType, int isWhite, int x, int y) {
    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, pieceTextures[isWhite][pieceType]);

    enableAlphaBlending();

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2i(x, y);

    glTexCoord2f(1.0f, 0.0f);
    glVertex2i(x + GRIDSIZE, y);

    glTexCoord2f(1.0f, 1.0f);
    glVertex2i(x + GRIDSIZE, y + GRIDSIZE);

    glTexCoord2f(0.0f, 1.0f);
    glVertex2i(x, y + GRIDSIZE);
    glEnd();

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}

void drawChessboard(void) 
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);  // White color

    bool isWhite = true;

    for (int i = 0; i < WINDOWWIDTH; i += GRIDSIZE) {
        for (int j = 0; j < WINDOWHEIGHT; j += GRIDSIZE) {
            if (isWhite) {
                glColor3f(0.466f, 0.6f, 0.329f);  // Black square
            } else {
                glColor3f(0.913f, 0.929f, 0.8f);  // White square
            }

            glBegin(GL_QUADS);
            glVertex2i(i, j);
            glVertex2i(i + GRIDSIZE, j);
            glVertex2i(i + GRIDSIZE, j + GRIDSIZE);
            glVertex2i(i, j + GRIDSIZE);
            glEnd();

            isWhite = !isWhite;
        }
        isWhite = !isWhite; // Offset the rows
    }

    for (int pieceType = 0; pieceType < 6; pieceType++) {
        long long unsigned int piece = 0;
        switch (pieceType) {
            case 0: piece = global_bitboards.rook; break;
            case 1: piece = global_bitboards.knight; break;
            case 2: piece = global_bitboards.bishop; break;
            case 3: piece = global_bitboards.queen; break;
            case 4: piece = global_bitboards.king; break;
            case 5: piece = global_bitboards.pawn; break;
        }

        piece = piece & global_bitboards.black_pieces;
        while (piece) {
            int square = __builtin_ffsll(piece) - 1;
            int x = (square % 8) * GRIDSIZE;
            int y = (7 - (square / 8)) * GRIDSIZE;
            drawPiece(pieceType, 0, x, y); // 0 indicates white pieces
            piece &= ~(((long long unsigned int)1) << square);
        }
    }
    // Draw black pieces based on your global_bitboards
    for (int pieceType = 0; pieceType < 6; pieceType++) {
        long long unsigned int piece = 0;
        switch (pieceType) {
            case 0: piece = global_bitboards.rook; break;
            case 1: piece = global_bitboards.knight; break;
            case 2: piece = global_bitboards.bishop; break;
            case 3: piece = global_bitboards.queen; break;
            case 4: piece = global_bitboards.king; break;
            case 5: piece = global_bitboards.pawn; break;
        }

        piece = piece & global_bitboards.white_pieces;
        while (piece) {
            int square = __builtin_ffsll(piece) - 1;
            int x = (square % 8) * GRIDSIZE;
            int y = (7 - (square / 8)) * GRIDSIZE;
            drawPiece(pieceType, 1, x, y); // 1 indicates black pieces
            piece &= ~(((long long unsigned int)1) << square);
        }
    }

    glFlush();
}

void display(void) 
{
    drawChessboard();
}

void init_display(int ac, char **av) 
{
    glutInit(&ac, av);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOWWIDTH, WINDOWHEIGHT);
    glutCreateWindow("Chessboard");

    initializeTextures();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOWWIDTH, 0, WINDOWHEIGHT);

    glutMouseFunc(onMouseClick);
    glutKeyboardFunc(onKeyPress);
    glutDisplayFunc(display);

    rewind_chess_board(true, true);

    glutMainLoop();
}