# Sistema Digital de Controle de Horas Extras - Base27

## Sobre o Projeto
Este projeto é um protótipo funcional desenvolvido em **Linguagem C** como parte do Projeto Integrador de Engenharia de Software. O objetivo é simular a lógica de automação do controle de horas extras para a startup **Base27**, substituindo processos manuais e garantindo maior confiabilidade nos cálculos e aprovações.

## Funcionalidades Implementadas
O sistema foca na validação das regras de negócio críticas:
* **Controle de Acesso:** Diferenciação entre perfil de Funcionário e Gestor.
* **Registro de Ponto:** Inserção de horas trabalhadas com classificação de dia (Útil/Fim de Semana).
* **Regra de Aprovação (Compliance):** O sistema bloqueia aprovações de horas extras fora da janela permitida (13h às 14h), conforme exigência operacional.
* **Cálculo Automático:** Aplicação de adicionais (50%, 100% e Noturno) sobre o salário base.
* **Relatórios:** Geração de extrato consolidado para folha de pagamento.

## Justificativa Técnica
A escolha da Linguagem C visa a **prototipagem lógica** e o fortalecimento dos fundamentos de engenharia de software (estruturas de dados e algoritmos). Embora não seja uma linguagem para interface web final, ela garante a performance e a validação correta das regras de negócio no backend antes da implementação em alto nível.
