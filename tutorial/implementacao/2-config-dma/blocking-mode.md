# Modo bloqueante
No modo bloqueante, o DMA aguarda o processador terminar a transferência antes de continuar. **Isso significa que o processador fica ocupado até que a transferência seja concluída.**

Utilizamos A função `dma_channel_wait_for_finish_blocking()`, que bloqueia a execução até que a transferência esteja completa:

```c
dma_channel_wait_for_finish_blocking(dma_channel)
```

Podemos criar uma função para lidar com essa espera e exibir os dados capturados:

```c
void await_dma_complete()
{
    // Espera a transferência terminar
    dma_channel_wait_for_finish_blocking(dma_channel);

    // Exibe as amostras
    print_samples();   

    // Reinicia a transferência            
    dma_channel_set_write_addr(dma_channel, (void *)adc_buffer, true); 
}
```
E depois apenas chamamos tudo na função `main()`:

## Finalizando nossa main
---
```c
int main()
{
    stdio_init_all();
    initialize_adc();
    initialize_dma();

    // Loop principal
    while (true)
    {
        printf("\nDMA Blocking\n");
        await_dma_complete();
        sleep_ms(1000);
    }

    return 0;
}
```
- A função `dma_channel_wait_for_finish_blocking()` é responsável por aguardar a transferência terminar
- A função `print_samples()` é responsável por exibir os dados capturados
- A função `dma_channel_set_write_addr()` é responsável por reiniciar a transferência

Pronto, agora você já pode executar o programa e ver os dados capturados no terminal.

---
## 🔗 Veja o código fonte completo [AQUI](../../../src/dma_init/dma_blocking.c)
---
## [Voltar](../../implementacao/2-config-dma/config-dma.md#4-modo-bloqueante-x-modo-com-interrupção)