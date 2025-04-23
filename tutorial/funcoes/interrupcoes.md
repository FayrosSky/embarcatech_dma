# Interrupções (IRQ) no DMA

As funções de IRQ permitem configurar e habilitar **interrupções** para que **você seja avisado automaticamente quando uma transferência DMA terminar (ou algum outro evento acontecer),** sem precisar ficar verificando manualmente.

## 1) `dma_irqn_set_channel_enabled()`
> Habilita interrupções para um canal DMA específico em um número de IRQ (0 ou 1).
  <details>
  <summary>Ver detalhes</summary>

  - **Função completa:** `void dma_irqn_set_channel_enabled(uint channel, uint dma_irq_num, bool enabled);`

   -   **Parâmetros:**
        -   `channel`: O número do canal DMA a ser configurado.
        -   `dma_irq_num`: O número do IRQ do DMA; 0 ou 1 (para `DMA_IRQ_0` ou `DMA_IRQ_1`)
        -   `enabled`: `true` para habilitar a interrupção, `false` para desabilitar.

  -   **Retorno:** Nenhum (void)
  </details>

---
## 2) `dma_channel_set_irq0_enabled()`
> Ativa a interrupção IRQ0 para um canal DMA, permitindo que ele gere eventos quando a transferência terminar.
  <details>
  <summary>Ver detalhes</summary>

  - **Função completa:** `void dma_channel_set_irq0_enabled(uint channel, bool enabled);`

   -   **Parâmetros:**
        -   `channel`: O número do canal DMA a ser configurado.
        -   `enabled`: `true` para habilitar a interrupção IRQ_0, `false` para desabilitar.

  -   **Retorno:** Nenhum (void)
  </details>

---
## 3) `dma_channel_set_irq1_enabled()`
> Ativa a interrupção IRQ1 para um canal DMA, mesma ideia do IRQ0, mas usando o segundo canal de interrupções disponível.
  <details>
  <summary>Ver detalhes</summary>

  - **Função completa:** `void dma_channel_set_irq1_enabled(uint channel, bool enabled);`

   -   **Parâmetros:**
        -   `channel`: O número do canal DMA a ser configurado.
        -   `enabled`: `true` para habilitar a interrupção IRQ1, `false` para desabilitar.

  -   **Retorno:** Nenhum (void)
  </details>

---
## [Voltar](../../READme.md#3-funções-associadas)