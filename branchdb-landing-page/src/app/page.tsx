import { cookedData, mainPageData } from "@/lib/mainPageData";
import { onest } from "./layout";
import { IoLogoGithub } from "react-icons/io5";
import { RiTwitterXFill } from "react-icons/ri";
import { IoLogoLinkedin, IoIosMail } from "react-icons/io";
import { SlGlobe } from "react-icons/sl";

const socials = [
  { href: "https://x.com/chandan_k_dev", Icon: RiTwitterXFill },
  { href: "https://www.linkedin.com/in/chandankhamitkar/", Icon: IoLogoLinkedin },
  { href: "mailto:khamitkar.dev@gmail.com", Icon: IoIosMail },
  { href: "https://github.com/ChandanKhamitkar", Icon: IoLogoGithub },
  { href: "https://chandankhamitkar.vercel.app/", Icon: SlGlobe },
];

export default function Home() {
  return (
    <div className={`w-full bg-black flex flex-col overflow-x-hidden custom-scrollbar rounded-md relative ${onest.className}`}>
      <div className="relative h-screen flex flex-col justify-center items-center">
        {/* Background Image */}
        <img
          src="orange-half-bottom-circle.avif"
          alt=""
          className="absolute inset-0 w-full h-full object-cover object-bottom z-0"
        />
        <div className="absolute inset-0 bg-black/40 z-10"></div>

        {/* Hero content */}
        <div className="flex flex-col items-center justify-center flex-1 relative z-20">
          <h1 className="md:text-7xl text-3xl lg:text-[190px] font-medium text-center bg-gradient-to-r from-white/80 via-yellow-100 to-white/80 bg-clip-text text-transparent drop-shadow-[0_2px_10px_rgba(255,255,255,0.3)]">
            BranchDB
          </h1>

          <p className="text-neutral-100/50 text-2xl font-extralight drop-shadow-[0_1px_6px_rgba(255,140,51,0.2)]">
            A durable, in-memory database built in C++.
          </p>
          <div className="w-[40rem] relative mt-4 opacity-50">
            <div className="absolute inset-x-20 top-0 bg-gradient-to-r from-transparent via-white to-transparent h-[2px] w-3/4 blur-sm" />
            <div className="absolute inset-x-20 top-0 bg-gradient-to-r from-transparent via-white to-transparent h-px w-3/4" />
            <div className="absolute inset-x-60 top-0 bg-gradient-to-r from-transparent via-white to-transparent h-[5px] w-1/4 blur-sm" />
            <div className="absolute inset-x-60 top-0 bg-gradient-to-r from-transparent via-white to-transparent h-px w-1/4" />
          </div>

        </div>
      </div>

      {/* Section-2 */}
      <div className="flex flex-col justify-center items-center py-20 bg-black relative">
        <div className="flex justify-center items-center mx-auto w-[90%] gap-6">
          <div className="h-px w-full bg-gradient-to-r from-transparent to-metaliclight rounded-full opacity-40"></div>
          <p className="text-7xl text-neutrall-100 font-medium text-nowrap">What is BranchDB?</p>
          <div className="h-px w-full bg-gradient-to-r from-metaliclight to-transparent rounded-full opacity-40"></div>
        </div>
        <p className="text-xl md:text-2xl text-neutral-500 max-w-5xl mx-auto text-center md:leading-10 mt-6">BranchDB is an open-source, in-memory key-value database written in <span className="px-2 py-1 rounded-xl bg-neutral-700/70 text-primary text-xl">C++</span> — built from scratch for performance, transparency, and developer control. It supports expiration, disk persistence, multi-threaded architecture, compact logging and multi-user architecture.</p>

        <img src="database.svg" alt="DataBase icon" className="absolute size-28 object-cover left-5 -rotate-12 top-1/2 transform -translate-y-1/3 blur-xs" />
        <img src="bracket-square.svg" alt="Key Value icon" className="absolute size-24 object-cover right-6 rotate-12 top-1/2 blur-xs" />
      </div>

      {/* What is branchDB*/}
      <div className="mt-10 flex justify-center items-stretch gap-6 h-max">
        {
          mainPageData.map((item, index) => <div key={index} className="flex flex-col justify-start items-start bg-neutral-950/30 border border-neutral-400/20 rounded-2xl p-6 relative w-96 overflow-clip">
            <img src="dots.svg" alt="Key Value icon" className="absolute w-full h-full object-cover inset-0 z-0 opacity-[7%]" />
            <div className="absolute inset-0 w-full hull bg-gradient-to-t from-black to-transparent"></div>

            <p className="text-3xl font-medium text-white drop-shadow-xl">{item.title}</p>
            <p className="text-sx font-light text-neutral-400 drop-shadow-xl mt-6">{item.desc}</p>
          </div>)
        }
      </div>

      {/* What i cooked up */}
      <div className="pb-20 pt-40 w-full flex flex-col justify-center items-center">
        <p className="text-7xl text-neutral-100 font-medium text-nowrap mx-auto w-fit">
          What I cooked up?
        </p>

        <div className="grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 gap-8 mt-16 mx-auto">
          {cookedData.map((item, index) => (
            <div
              key={index}
              className="bg-gradient-to-b from-primary/50 via-primary/10 to-transparent rounded-2xl p-[3px]"
            >
              <div className="w-[320px] h-[400px] bg-neutral-950 flex flex-col items-center rounded-2xl p-6 relative overflow-hidden text-center">
                {/* Background */}
                <img
                  src="cooked-bg.svg"
                  alt=""
                  className="absolute inset-0 object-cover opacity-50 pointer-events-none"
                />

                {/* Title */}
                <p className="text-2xl font-medium text-white drop-shadow-xl uppercase">
                  {item.title}
                </p>

                {/* Icon */}
                <div className="flex-1 flex items-center justify-center">
                  <img
                    src={item.imageLink}
                    alt=""
                    className="w-32 h-32 object-contain"
                  />
                </div>

                {/* Description */}
                <p className="text-md font-light text-neutral-400 drop-shadow-xl mt-4">
                  {item.desc}
                </p>
              </div>
            </div>
          ))}
        </div>
      </div>

      {/* Benchmarks */}
      <div className="py-20 w-full flex flex-col justify-center items-center">
        <div className="flex justify-center items-center">
          <img src="benchmarks.svg" alt="Settings icon" className="size-20 object-contain mr-4" />
          <p className="text-7xl text-neutral-100 font-medium text-nowrap mx-auto w-fit">
            Benchmarks
          </p>
        </div>
        <img src="benchmarks-card.jpg" alt="Benchmark Details" className="w-[70%] object-contain mt-14 rounded-3xl" />
        <p className="mt-6 md:mt-12 text-base text-gray-400 text-center w-[90%] md:w-[70%]">Note: Benchmarks were conducted on an Lenovo ideapad Slim 3, 64-bit operating system with 8 GB RAM, 11th Gen Intel(R). Results may vary on different hardware.</p>
      </div>

      {/* Support us */}
      <div className="py-40 w-full flex flex-col justify-center items-center">
        <p className="text-6xl text-neutral-100 font-medium text-nowrap mx-auto w-fit mb-6">
          Blown away? Give us a boost!
        </p>

        <a
          href="https://github.com/ChandanKhamitkar/BranchDB"
          target="_blank"
          rel="noopener noreferrer"
          className="relative inline-flex w-fit h-fit overflow-hidden rounded-xl p-[1.5px] mt-6 cursor-pointer"
        >
          <span className="absolute inset-[-1000%] animate-[spin_2s_linear_infinite] bg-[conic-gradient(from_90deg_at_50%_50%,#ff0000_0%,#ff7f00_16%,#ffff00_33%,#00ff00_50%,#0000ff_66%,#8b00ff_83%,#ff0000_100%)]" />
          <span className="inline-flex h-full w-full items-center justify-center rounded-xl bg-black px-12 py-4 text-lg font-medium text-white backdrop-blur-xl">
            GitHub
            <IoLogoGithub className="size-8 ml-4" />
          </span>
        </a>
      </div>

      {/* Meet Developer */}
      <div className="pt-10 w-full h-fit flex flex-col justify-between relative overflow-clip">
        {/* Absolutes */}
        <img
          src="gradii-1.png"
          alt="Meet Developer Background Image"
          className="absolute inset-0 w-full rounded-b-4xl opacity-65 z-0 object-cover"
        />
        <img
          src="name-line.svg"
          alt="Developer Name"
          className="absolute bottom-10 left-0 z-20 h-1/2"
        />
        <div className="absolute inset-0 bg-gradient-to-r from-black/30 to-transparent z-10"></div>

        <p className="text-4xl md:text-8xl font-medium mb-12 text-neutral-500 text-center mx-auto z-20">
          Meet The Developer
        </p>

        <div className="grid grid-cols-1 md:grid-cols-2 gap-8 px-6 md:px-12 relative z-20">
          {/* Profile Pic */}
          <div className="flex justify-center">
            <div
              className="w-[85%] max-w-[420px] aspect-[4/5] md:aspect-[3/4] h-auto flex items-end overflow-hidden"
              aria-hidden="false"
            >
              <img
                src="me.png"
                alt="Chandan Khamitkar's Profile Pic"
                className="w-full h-full object-contain object-bottom transform translate-y-[2px]"
              />
            </div>
          </div>

          <div className="flex flex-col justify-center items-start">
            <p className="text-lg md:text-xl font-medium text-neutral-400 leading-8 mb-6"> I'm an{" "}
              <span className="px-3 py-1 rounded-3xl bg-white/30 backdrop-blur-lg text-neutral-900">Engineer</span>  fascinated by the art of system design, databases — the more rooted in the core, the better.
            </p>
            <p className="text-lg md:text-xl font-semibold text-neutral-400 leading-8 mb-6"> 2x Full Stack Developer Intern | 3x Hackathon Winner
            </p>

            {/* Pre Works */}
            <p className="text-2xl text-neutral-100 font-medium mt-6">Prev Works</p>
            <div className="flex items-center mt-4">
              <a href="https://github.com/ChandanKhamitkar/BillBot" className="underline underline-offset-4 font-semibold text-neutral-300\ text-xl tracking-wide text-neutral-100 mr-1">BillBot</a>
              <p className="text-lg text-neutral-400"> - From text to invoice in a snap.</p>
            </div>
            <p className="text-xl md:text-4xl font-medium italic text-neutral-300 leading-8 my-16"> <span className="text-7xl font-serif">"</span> Design for scale. Build for clarity.
            </p>

            {/* Social Icons */}
            <div className="flex items-center space-x-4">
              {socials.map(({ href, Icon }, idx) => (
                <a key={idx} href={href} target="_blank" rel="noopener noreferrer">
                  <Icon size={30} className="hover:scale-110 transition-all duration-300" />
                </a>
              ))}
            </div>

          </div>
        </div>
      </div>


      <div className="py-30"></div>
    </div >
  );
}