import {
  Footer,
  FooterCopyright,
  FooterLink,
  FooterLinkGroup,
} from "flowbite-react";

export function Foot() {
  return (
    <Footer container>
      <FooterCopyright href="/" by="MyVet System" year={2024} />
      <FooterLinkGroup>
        <FooterLink href="#">Sobre Nosotros</FooterLink>
        <FooterLink href="#">Servicios</FooterLink>
        <FooterLink href="#">Politica de Privacidad</FooterLink>
        <FooterLink href="#">Contacto</FooterLink>
      </FooterLinkGroup>
    </Footer>
  );
}
