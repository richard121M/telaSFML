#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <string>

// Definições de tamanho da janela e do quadrado
const float JANELA_LARGURA = 700.0f;
const float JANELA_ALTURA = 300.0f;
const float QUADRADO_TAMANHO = 200.0f;

int main(int argc, char* argv[]) {
    // 1. Inicializa o subsistema de vídeo na SDL3
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Erro ao inicializar SDL3: %s\n", SDL_GetError());
        return 1;
    }

     // 2. Cria a janela e o renderizador ativando o V-Sync (SDL_PROP_RENDERER_CREATE_PRESENTVSYNC_NUMBER)
    SDL_Window* janela = NULL;
    SDL_Renderer* renderizador = NULL;

    // Criamos uma estrutura de propriedades para o renderizador
    SDL_PropertiesID props = SDL_CreateProperties();
    SDL_SetStringProperty(props, SDL_PROP_RENDERER_CREATE_NAME_STRING, NULL);
    SDL_SetNumberProperty(props, SDL_PROP_RENDERER_CREATE_PRESENT_VSYNC_NUMBER, 1);

    // Cria a janela normalmente
    janela = SDL_CreateWindow("Quadrado Centralizado - SDL3", (int)JANELA_LARGURA, (int)JANELA_ALTURA, 0);
    if (!janela) {
        SDL_Log("Erro ao criar janela: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Vincula o renderizador com V-Sync à janela
    SDL_SetPointerProperty(props, SDL_PROP_RENDERER_CREATE_WINDOW_POINTER, janela);
    renderizador = SDL_CreateRendererWithProperties(props);
    SDL_DestroyProperties(props); // Limpa as propriedades da memória

    if (!renderizador) {
        SDL_Log("Erro ao criar renderizador: %s\n", SDL_GetError());
        SDL_DestroyWindow(janela);
        SDL_Quit();
        return 1;
    }

    // 3. Define a posição e tamanho usando SDL_FRect (Ponto Flutuante / Alta Precisão)
    SDL_FRect quadrado;
    quadrado.w = QUADRADO_TAMANHO; // Largura
    quadrado.h = QUADRADO_TAMANHO; // Altura
    // Fórmulas para centralizar no meio da tela
    quadrado.x = (JANELA_LARGURA / 2.0f) - (QUADRADO_TAMANHO / 2.0f);
    quadrado.y = (JANELA_ALTURA / 2.0f) - (QUADRADO_TAMANHO / 2.0f);

    // Loop principal
    bool rodando = true;
    SDL_Event evento;

    // Variáveis para o cálculo correto de FPS
    Uint64 frames = 0;
    Uint64 lastTime = SDL_GetTicks(); // Inicializa com o tick atual (Uint64)

    while (rodando) {
        Uint64 currentTick = SDL_GetTicks();

        while (SDL_PollEvent(&evento)) {
            if (evento.type == SDL_EVENT_QUIT) {
                rodando = false;
            }
        }

        // Limpa a tela com fundo preto
        SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 255);
        SDL_RenderClear(renderizador);

        // Define a cor do quadrado (Vermelho)
        SDL_SetRenderDrawColor(renderizador, 255, 0, 0, 255);

        // Desenha o quadrado preenchido
        SDL_RenderFillRect(renderizador, &quadrado);

        // Atualiza a tela
        SDL_RenderPresent(renderizador);
        SDL_Delay(16);
        // Incrementa o contador de frames a cada renderização
        frames++;

        // Verifica se já se passou 1 segundo (1000 milissegundos)
        if (currentTick >= lastTime + 1000) {
            std::string titulo = "Jogo - FPS: " + std::to_string(frames);
            SDL_SetWindowTitle(janela, titulo.c_str());

            frames = 0; // Reseta o contador para o próximo segundo
            lastTime = currentTick; // Atualiza o marcador de tempo corretamente
        }
    }

    // 4. Limpeza e encerramento (SDL3 limpa automaticamente os renderizadores associados)
    SDL_DestroyWindow(janela);
    SDL_Quit();

    return 0;
}
