# Gerenciamento de Canais DMA

As funções de gerenciamento permitem **reivindicar** (reservar) ou **liberar** canais DMA, garantindo que você não tente usar um canal que já esteja em uso por outra parte do código.

## 1) `dma_claim_mask()`
> É usada para marcar múltiplos canais DMA como "em uso" ou "reservados" de uma vez.
  <details>
  <summary>Ver detalhes</summary>

  - **Função completa:**`void dma_claim_mask(uint32_t mask);`

   -   **Parâmetros:**
        -   `mask`: Uma máscara de bits onde cada bit representa um canal DMA.

  -   **Retorno:** Nenhum (void)
  </details>

---
## 2) `dma_channel_claim()`
> Reivindica (reserva) um canal DMA específico para garantir que ninguém mais o use.
  <details>
  <summary>Ver detalhes</summary>

  - **Função completa:** `bool dma_channel_claim(uint channel);`

   -   **Parâmetros:**
        -   `channel`: O número do canal DMA a ser reivindicado.

  -   **Retorno:**
      -   `true` para reivindicar o canal, `false` caso contrário.
  </details>

---
## 3) `dma_channel_unclaim()`
> Libera um canal DMA que você tinha reivindicado, tornando-o disponível para outro uso.
  <details>
  <summary>Ver detalhes</summary>

  - **Função completa:** `void dma_channel_unclaim(uint channel);`

   -   **Parâmetros:**
        -   `channel`: O número do canal DMA a ser liberado.

  -   **Retorno:** Nenhum (void)
  </details>

---
## 4) `dma_claim_unused_channel()`
> Busca e reivindica automaticamente o próximo canal DMA que estiver livre.
  <details>
  <summary>Ver detalhes</summary>

  - **Função completa:** `uint dma_claim_unused_channel(bool panic_if_none);`

   -   **Parâmetros:**
        -   `panic_if_none`:
            - Se `true`, a função causará um panic (interrupção do programa com mensagem de erro) se não houver nenhum canal DMA disponível.
            - Se `false`, a função retornará `(uint)PICO_ERROR_GENERIC` se não houver canal disponível (permitindo que o programa tente lidar com a situação de outra forma)
                > Basicamente, é um erro não destrutivo...

  -   **Retorno:**
      -   Se a função encontrar um canal DMA livre, ela retorna o número desse canal (um número inteiro), ou `-1` se não achar nenhum canal livre.
  </details>

---
## [Voltar](../../READme.md#3-funções-associadas)  ----------------------------------------- Próx.: [Funções de Interrupção](./interrupcoes.md)