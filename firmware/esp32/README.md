# Firmware ESP32-S3 — Sabre 3D

Área de desenvolvimento do firmware embarcado do Sabre 3D.

**Status: planejamento / não funcional.** Nenhum arquivo nesta pasta deve ser considerado firmware pronto para operar uma impressora.

## Objetivo

Hospedar a interface web na rede Wi-Fi local, receber G-code, armazená-lo no microSD e transmitir comandos por USB Host à controladora Marlin, com controle de fluxo e mecanismos de segurança.

## Estrutura

- `src/` — código-fonte C/C++ do firmware.
- `include/` — cabeçalhos e configurações.
- `lib/` — componentes próprios do projeto.
- `data/` — arquivos estáticos da interface web para servir no ESP32.
- `config/` — exemplos de configuração, sem credenciais reais.
- `test/` — testes automatizados e simuladores.
- `hardware/` — esquemas, pinagem e notas elétricas.

## Antes de implementar

1. Confirmar o modelo exato da placa ESP32-S3 e suas conexões USB Host, alimentação e microSD.
2. Definir o ambiente de compilação (ESP-IDF ou PlatformIO).
3. Validar a enumeração USB e o chipset USB-serial de cada impressora (CH340, CP210x, FTDI, CDC-ACM etc.).
4. Implementar comunicação Marlin com respostas `ok`, tratamento de `busy`/`Resend` e parada segura.
5. Validar proteção contra alimentação reversa USB, falhas térmicas e perda de comunicação.

**Importante:** a fonte 5 V do ESP32 será independente da impressora. O hardware USB Host precisa fornecer VBUS corretamente, sem retroalimentar o circuito.

Desenvolvido por DGandra - 2026.
