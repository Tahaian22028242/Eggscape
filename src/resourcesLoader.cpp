#include "header/resourcesPath.hpp"

SDL_Texture* loadTexture(const char* filePath, SDL_Renderer* renderer) {
    SDL_Surface* tempSurface = IMG_Load(filePath);
    if (!tempSurface) {
        std::cerr << "Failed to load image of function: " << IMG_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    if (!texture) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
    }
    return texture;
}

Mix_Chunk* loadSound(const char* filePath) {
    Mix_Chunk* sound = Mix_LoadWAV(filePath);
    if (!sound) {
        std::cerr << "Failed to load sound: " << Mix_GetError() << std::endl;
    }
    return sound;
}

void renderSprite(SDL_Texture* sprite ,SDL_Renderer* renderer, int x, int y, int width, int height) {
    SDL_Rect sprite_rect = { x, y, width, height };
    SDL_RenderCopy(renderer, sprite, NULL, &sprite_rect);
}

void Draw_Font(SDL_Renderer *renderer, const char *str, int x, int y, int width, int height, int size, SDL_Color color) {
    TTF_Font* font = TTF_OpenFont(fontPath, size);
    
    SDL_Surface* message_surf = TTF_RenderText_Blended(font, str, color);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, message_surf);
    SDL_Rect Message_rect = {x, y, width, height};
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
    
    SDL_DestroyTexture(Message);
    SDL_FreeSurface(message_surf);
    TTF_CloseFont(font);
}