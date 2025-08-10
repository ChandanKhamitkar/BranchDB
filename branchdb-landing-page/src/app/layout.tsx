import type { Metadata } from "next";
import { Open_Sans } from "next/font/google";
import "./globals.css";
import { NavbarDemo } from "@/components/Navbar";

export const openSans = Open_Sans({
  variable: "--font-open-sans",
  subsets: ["latin"],
  weight: ['400', '500', '700']
});

export const metadata: Metadata = {
  title: "BranchDB",
  description: "BranchDB a lightweight a Key-Value Store, with in-memory data & disk persistence built in C++.",
};

export default function RootLayout({
  children,
}: Readonly<{
  children: React.ReactNode;
}>) {
  return (
    <html lang="en">
      <body
        className={`${openSans.variable} antialiased`}
      >

        <div className="fixed top-0 left-0 w-full z-50 bg-transparent mt-6">
          <NavbarDemo />
        </div>
        {children}
      </body>
    </html>
  );
}
