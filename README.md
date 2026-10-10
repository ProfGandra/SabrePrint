# SabrePrint — Sabre 3D

Interface web para gerenciamento de impressão 3D por ESP32-S3, com upload de G-code, armazenamento microSD e transmissão USB serial para impressoras com Marlin.

## Estado

Protótipo web v0.3 desenvolvido localmente, ainda pendente de envio ao repositório. O protótipo simula os comandos, sem movimentar impressora real.

## Planejamento

- Interface web responsiva e tela de abertura com identidade pirata.
- Rodapé: Desenvolvido por DGandra - 2026.
- Upload de arquivos G-code para armazenamento no ESP32 (etapa futura).
- Comunicação USB Host com Marlin (etapa futura).
- Alimentação externa do ESP32-S3.

## Estrutura planejada

`index.html`, `assets/`, `css/`, `js/`, `firmware/esp32/` e `docs/`.
