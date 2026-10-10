# Sabre 3D — Lista de materiais (BOM)

**Estado:** planejamento; lista preliminar sujeita à validação elétrica e mecânica.

| Item | Componente | Qtde. | Especificação / observação |
|---|---|---:|---|
| 1 | Placa ESP32-S3 | 1 | Preferência: ESP32-S3-DevKitC-1, variante **N16R8** (16 MB flash, 8 MB PSRAM); conferir pinagem e revisão antes da compra |
| 2 | Módulo leitor de cartão microSD | 1 | Interface **SPI**, lógica de **3,3 V** compatível com ESP32-S3; evitar módulos que imponham sinais de 5 V |
| 3 | Cartão microSD | 1 | 16 ou 32 GB, preferencialmente classe 10, para arquivos G-code; validar formato e compatibilidade |
| 4 | Fonte externa regulada | 1 | **5 V CC**, corrente sugerida **2 A ou mais**; dimensionamento final depende do ESP32, cartão e circuito USB Host |
| 5 | Conector de alimentação tipo P4 (jack DC) | 1 | Preferência provisória **5,5 × 2,1 mm**, polaridade **centro positivo**; deve corresponder ao plugue da fonte |
| 6 | Cabo USB para programação/alimentação de dados do ESP32-S3 | 1 | **USB-A ↔ USB-C** ou **USB-C ↔ USB-C**, conforme a porta do computador e da placa escolhida; cabo **com dados**, não apenas carga |
| 7 | Cabo USB para comunicação ESP32-S3 ↔ impressora | 1 | Conector na impressora a verificar: frequentemente **USB-B**, **mini-USB** ou **micro-USB**; extremidade host dependerá do circuito/conector USB Host escolhido |
| 8 | Gabinete / case | 1 | **Projeto a desenvolver**, preferencialmente impresso em 3D, com fixação do ESP32, microSD, P4, conectores e ventilação |
| 9 | Circuito/conector USB Host com VBUS 5 V | 1 | **Obrigatório para a arquitetura USB Host**; pode exigir conector USB-A fêmea, proteção de corrente, chave de alimentação e adaptação conforme a placa |
| 10 | Proteção de alimentação | 1 conjunto | Proteção contra inversão de polaridade e sobrecorrente; avaliar fusível e prevenção de retorno de alimentação entre impressora e ESP32 |
| 11 | Cabos, conectores e elementos de montagem | 1 conjunto | Fios, conectores, espaçadores, parafusos e fixação conforme protótipo e gabinete |

## Requisitos e decisões

- O ESP32-S3 terá **alimentação independente** da impressora, por fonte externa de **5 V CC** e conector P4.
- **Não aplicar 5 V diretamente a pinos de GPIO ou ao pino 3V3.** A entrada de 5 V precisa ser compatível com a placa e o circuito escolhido.
- A conexão com a impressora será **USB Host**, usando comunicação USB-serial compatível com a controladora e o firmware Marlin. O USB OTG nativo do ESP32-S3 **não dispensa** circuito correto de VBUS nem suporte de software ao chipset USB-serial.
- A interface web e os arquivos G-code ficarão no sistema do ESP32/microSD; **não será necessário gravar o G-code na memória da impressora**.
- O **gabinete será projetado após a definição física dos conectores e a validação elétrica**.
- **Antes de comprar o cabo de impressora**, identificar o tipo de porta USB de cada máquina (RAMPS, Ender 3, Ender 5 Plus e JG Aurora A5S). Pode ser necessário mais de um tipo de cabo.
- Verificar se a variante N16R8, a placa de desenvolvimento e a porta USB disponível correspondem ao perfil configurado no PlatformIO.

## Próximas validações

1. Selecionar a placa ESP32-S3 exata e levantar seu esquema/pinagem.
2. Definir o circuito USB Host, alimentação VBUS e conectores.
3. Definir os pinos SPI do microSD sem conflito com USB e demais periféricos.
4. Desenhar o esquema elétrico e iniciar o modelo CAD do case.
5. Validar consumo e temperatura antes de fechar o gabinete.

**Desenvolvido por DGandra - 2026**
