# Controle de Execução do DMA

## 1) `dma_channel_start()`
> Inicia a transferência de dados em um canal DMA previamente configurado.
  <details>
  <summary>Ver detalhes</summary>

  - **Função completa:** `void dma_channel_start(uint channel);`

   -   **Parâmetros:**

          -   `channel`: O número do canal DMA a ser iniciado.

  -   **Retorno:** Nenhum (void)
  </details>

---
## 2) `dma_channel_abort()`
> Interrompe imediatamente uma transferência DMA que esteja em andamento.
  <details>
  <summary>Ver detalhes</summary>

  - **Função completa:** `void dma_channel_abort(uint channel);`

   -   **Parâmetros:**
        - `channel`: O número do canal DMA a ser abortado.

  -   **Retorno:** Nenhum (void)

### Um detalhe importante...

Quando você chama essa função, ela força o DMA a parar a transferência de dados naquele canal. No entanto, no RP2040, em certas situações, quando você chama `dma_channel_abort` para parar o DMA, **o processo de parada não é instantâneo.**

O DMA pode já ter começado a ler um pedaço de dado, mas ainda não o escreveu no destino. Então, mesmo chamamdo o abort, quando o DMA terminar de escrever esse último dado, ele pode gerar um sinal de "transferência completa" (uma interrupção de conclusão). O que não deveria ocorrer...

### A solução
Se o seu programa usa interrupções para saber quando as transferências do DMA terminam, o ideal é você desativar e reativar a interrupção do DMA ao redor da chamada para `dma_channel_abort`:

```c
// Desativar a interrupção do DMA
dma_channel_set_irq0_enabled(channel, false);

// Interromper o canal DMA
dma_channel_abort(channel);

 // Reativar a interrupção do DMA
dma_channel_set_irq0_enabled(channel, true);
 ```
</details>

---
## 3) `dma_channel_is_busy()`
> Verifica se o canal DMA ainda está ocupado realizando uma transferência.
  <details>
  <summary>Ver detalhes</summary>

  - **Função completa:** `bool dma_channel_is_busy(uint channel);`

   -   **Parâmetros:**

        - `channel`: O número do canal DMA a ser verificado.

  -   **Retorno:**
      -   `true` se o canal estiver ocupado, `false` caso contrário.
  </details>

---
## 4) `dma_channel_wait_for_finish_blocking()`
> Faz o programa esperar (de forma bloqueante) até que a transferência do canal DMA termine.
  <details>
  <summary>Ver detalhes</summary>

  - **Função completa:** `void dma_channel_wait_for_finish_blocking(uint channel);`

   -   **Parâmetros:**
        -   `channel`: O número do canal DMA a ser aguardado.

  -   **Retorno:** Nenhum (void)

   > Essa função acaba "perdendo" o motivo do DMA, que é executar a transferência de dados em paralelo com outras tarefas do sistema. No entanto, pode ser necessária em alguns casos
  </details>

---
## [Voltar](../../READme.md#3-funções-associadas)  ----------------------------------------- Próx.: [Funções de Gerenciamento](./gerenciamento.md)