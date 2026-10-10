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
2. Ambiente definido: **PlatformIO com framework ESP-IDF**.
3. Validar a enumeração USB e o chipset USB-serial de cada impressora (CH340, CP210x, FTDI, CDC-ACM etc.).
4. Implementar comunicação Marlin com respostas `ok`, tratamento de `busy`/`Resend` e parada segura.
5. Validar proteção contra alimentação reversa USB, falhas térmicas e perda de comunicação.

**Importante:** a fonte 5 V do ESP32 será independente da impressora. O hardware USB Host precisa fornecer VBUS corretamente, sem retroalimentar o circuito.

## Identidade visual compartilhada

A interface web de referência fica na raiz do repositório (`/index.html`) e utiliza `/assets/capitao-dgandra.png` como carimbo de assinatura do Capitão DGandra, além de `/assets/sabre3d-logo.png`.

A interface destinada ao ESP32 deve preservar esses arquivos e seus caminhos relativos ao ser integrada ao servidor HTTP embarcado. A pasta `data/` é reservada para os recursos web do firmware; **a sincronização e o servidor web ainda não estão implementados**.

O modo de rede definido é **Wi-Fi SoftAP `Sabre3D`**, com acesso previsto por `http://192.168.4.1`. Não exige display ou roteador.

Desenvolvido por DGandra - 2026.
