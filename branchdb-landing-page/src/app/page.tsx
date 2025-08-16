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
        <div className="flex flex-col items-center justify-center flex-1 relative z-20 px-4 sm:px-6">
          <h1 className="text-6xl sm:text-8xl md:text-9xl lg:text-[190px] font-medium text-center bg-gradient-to-r from-white/80 via-yellow-100 to-white/80 bg-clip-text text-transparent drop-shadow-[0_2px_10px_rgba(255,255,255,0.3)]">
            BranchDB
          </h1>

          <p className="text-neutral-100/50 text-sm sm:text-lg md:text-xl lg:text-2xl font-extralight drop-shadow-[0_1px_6px_rgba(255,140,51,0.2)] text-center mt-2 sm:mt-0">
            A durable, in-memory database built in C++.
          </p>
          {/* Gradient Store line */}
          <div className="w-[20rem] md:w-[40rem] relative mt-4 opacity-50 mx-auto">
            <div className="absolute inset-x-20 top-0 bg-gradient-to-r from-transparent via-white to-transparent h-[2px] w-3/4 blur-sm" />
            <div className="absolute inset-x-20 top-0 bg-gradient-to-r from-transparent via-white to-transparent h-px w-3/4" />
            <div className="absolute inset-x-60 top-0 bg-gradient-to-r from-transparent via-white to-transparent h-[5px] w-1/4 blur-sm" />
            <div className="absolute inset-x-60 top-0 bg-gradient-to-r from-transparent via-white to-transparent h-px w-1/4" />
          </div>

        </div>
      </div>

      {/* Section-2 */}
      <div className="flex flex-col justify-center items-center py-20 bg-black relative px-4 md:px-6">
        <div className="flex justify-center items-center mx-auto w-[90%] gap-2 sm:gap-6">
          <div className="h-px w-full bg-gradient-to-r from-transparent to-metaliclight rounded-full opacity-40"></div>
          <p className="text-4xl md:text-7xl text-neutrall-100 font-medium text-center">What is BranchDB?</p>
          <div className="h-px w-full bg-gradient-to-r from-metaliclight to-transparent rounded-full opacity-40"></div>
        </div>

        <p className="text-base sm:text-xl md:text-2xl text-neutral-500 max-w-5xl mx-auto text-center leading-7 md:leading-10 mt-6">BranchDB is an open-source, in-memory key-value database written in <span className="px-2 py-1 rounded-xl bg-neutral-700/70 text-primary text-sm sm:text-xl">C++</span> — built from scratch for performance, transparency, and developer control. It supports expiration, disk persistence, multi-threaded architecture, compact logging and multi-user architecture.</p>

        <img src="database.svg" alt="DataBase icon" className="absolute size-16 sm:size-20 md:size-28 object-cover left-5 -rotate-12 top-0 lg:top-1/2 transform translate-y-1/2 lg:-translate-y-1/3 blur-xs" />
        <img src="bracket-square.svg" alt="Key Value icon" className="absolute size-12 sm:size-18 md:size-24 object-cover right-6 rotate-12 top-0 translate-y-3/4 lg:translate-y-0 lg:top-1/2 blur-xs" />
      </div>

      {/* What is branchDB*/}
      <div className="md:mt-10 flex flex-col md:flex-row justify-center items-center md:items-stretch gap-6 h-max px-6">
        {
          mainPageData.map((item, index) => <div key={index} className="flex flex-col justify-start items-start bg-neutral-950/30 border border-neutral-400/20 rounded-2xl p-6 relative w-fit sm:w-96 overflow-clip">
            <img src="dots.svg" alt="Key Value icon" className="absolute w-full h-full object-cover inset-0 z-0 opacity-[7%]" />
            <div className="absolute inset-0 w-full hull bg-gradient-to-t from-black to-transparent"></div>

            <p className="text-2xl sm:text-3xl font-medium text-white drop-shadow-xl">{item.title}</p>
            <p className="text-xs sm:text-sx font-light text-neutral-400 drop-shadow-xl mt-8 sm:mt-6 leading-5 sm:leading-normal">{item.desc}</p>
          </div>)
        }
      </div>

      {/* What i cooked up */}
      <div className="pb-20 pt-20 md:pt-40 w-full flex flex-col justify-center items-center px-4 sm:px-6">
        <p className="text-4xl md:text-7xl text-neutral-100 font-medium text-center mx-auto w-fit">
          What I cooked up?
        </p>

        <div className="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-3 gap-8 mt-14 md:mt-16 mx-auto">
          {cookedData.map((item, index) => (
            <div
              key={index}
              className="bg-gradient-to-b from-primary/50 via-primary/10 to-transparent rounded-2xl p-[3px]"
            >
              <div className="w-[270px] sm:w-[320px] h-[300px] sm:h-[400px] bg-neutral-950 flex flex-col items-center rounded-2xl p-6 relative overflow-hidden text-center">
                {/* Background */}
                <img
                  src="cooked-bg.svg"
                  alt=""
                  className="absolute inset-0 object-cover opacity-50 pointer-events-none"
                />

                {/* Title */}
                <p className="text-xl sm:text-2xl font-medium text-white drop-shadow-xl uppercase">
                  {item.title}
                </p>

                {/* Icon */}
                <div className="flex-1 flex items-center justify-center">
                  <img
                    src={item.imageLink}
                    alt=""
                    className="w-28 sm:w-32 h-28 sm:h-32 object-contain"
                  />
                </div>

                {/* Description */}
                <p className="text-sm sm:text-md font-light text-neutral-400 drop-shadow-xl mt-4">
                  {item.desc}
                </p>
              </div>
            </div>
          ))}
        </div>
      </div>

      {/* Performance */}
      <div className="py-10 sm:py-20 w-full flex flex-col justify-center items-center px-2 sm:px-6">
        <p className="text-4xl md:text-7xl text-neutral-100 font-medium mx-auto w-fit text-center">
          Performance Test
        </p>
        <div className="flex justify-center items-center">
          {/* <img src="benchmarks.svg" alt="Settings icon" className="size-9 sm:size-12 md:size-16 object-contain mr-4" /> */}
        </div>
        <div className="grid grid-cols-1 md:grid-cols-2 w-[90%] gap-6 mt-12">
          <img src="benchmarks-card-reqs.png" alt="Benchmark Requests Details" className="w-full object-contain" />
          <img src="benchmarks-card-clients.png" alt="Benchmark Client Details" className="w-full object-contain" />
        </div>
        <p className="mt-6 md:mt-12 text-xs lg:text-base text-gray-400 text-center w-[90%] md:w-[70%] leading-5 sm:leading-normal">Note: Performance tests were conducted on an Lenovo ideapad Slim 3, 64-bit operating system with 8 GB RAM, 11th Gen Intel(R). Results may vary on different hardware.</p>
      </div>

      {/* Support us */}
      <div className="py-16 sm:py-40 w-full flex flex-col justify-center items-center px-6">
        <p className="text-3xl sm:text-4xl md:text-5xl lg:text-6xl text-neutral-100 font-medium mx-auto w-fit mb-6 text-center">
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

      {/* The Brains - Improved Responsive Version */}
      <div id="meet_developer" className="pt-10 w-full h-fit flex flex-col justify-between relative overflow-clip rounded-b-4xl">
        {/* Background Image */}
        <img
          src="gradii-1.png"
          alt="Meet Developer Background Image"
          className="absolute inset-0 w-full h-full rounded-b-4xl opacity-65 z-0 object-cover"
        />

        {/* Gradient Overlay */}
        <div className="absolute inset-0 bg-gradient-to-r from-black/45 to-transparent z-10"></div>

        {/* Developer Name Image */}
        <img
          src="long-name.svg"
          alt="Developer Name"
          className="w-[85%] absolute bottom-0 left-1/2 -translate-x-1/2 z-20"
        />

        {/* Main Title */}
        <div className="relative z-20 mb-8 sm:mb-12">
          <p className="text-4xl sm:text-5xl lg:text-6xl xl:text-8xl font-medium text-neutral-500 text-center mx-auto px-4">
            The Brains
          </p>
        </div>

        {/* Main Content Container */}
        <div className="relative z-20 px-4 sm:px-6 lg:px-8 xl:px-12 pb-8 sm:pb-12">

          {/* Mobile Layout (up to md) */}
          <div className="block lg:hidden">
            {/* Profile Section - Mobile First */}
            <div className="flex justify-center mb-8 sm:mb-12 relative">
              {/* Circle background */}
              <div className="w-[280px] h-[280px] sm:w-[350px] sm:h-[350px] bg-black/20 rounded-full backdrop-blur-md absolute top-1/2 left-1/2 -translate-x-1/2 -translate-y-1/2 pointer-events-none"></div>

              {/* Profile image container with circular clipping */}
              <div className="w-[280px] h-[280px] sm:w-[350px] sm:h-[350px] rounded-full overflow-hidden relative z-25 flex items-end justify-center">
                <img
                  src="me.png"
                  alt="Chandan Khamitkar's Profile Pic"
                  className="w-[200px] h-[250px] sm:w-[240px] sm:h-[300px] object-contain object-bottom"
                />
              </div>
            </div>

            {/* Info Section - Mobile */}
            <div className="space-y-6 sm:space-y-8 text-left">
              {/* Engineer Description */}
              <div className="space-y-4">
                <p className="text-base sm:text-lg font-medium text-neutral-300 leading-7 sm:leading-8">
                  I'm an <span className="px-2 py-1 rounded-2xl bg-white/30 backdrop-blur-lg text-neutral-900 text-sm sm:text-base">Engineer</span> fascinated by the art of system design and databases.
                </p>
                <p className="text-base sm:text-lg font-semibold text-neutral-400 leading-7 sm:leading-8">
                  2x Full Stack Developer Intern&nbsp;|&nbsp;3x Hackathon Winner
                </p>
              </div>

              {/* Quote Section */}
              <div className="">
                <p className="text-base sm:text-lg font-medium text-neutral-300 leading-7 mb-8">
                  The more rooted in the core, the better.
                </p>
                <p className="text-2xl font-medium italic text-neutral-200 leading-8">
                  <span className="text-3xl sm:text-4xl align-[-0.2em]">" </span>
                  Design for scale.<br />Build for clarity.
                </p>
              </div>

              {/* Previous Works */}
              {/* <div>
                <p className="text-lg sm:text-xl text-neutral-100 font-medium mb-3">Prev Works</p>
                <div className="flex flex-col sm:flex-row sm:items-center">
                  <a
                    href="https://github.com/ChandanKhamitkar/BillBot"
                    className="underline underline-offset-4 font-semibold text-neutral-100 text-sm sm:text-base mb-2 sm:mb-0 sm:mr-2"
                    target="_blank"
                    rel="noopener noreferrer"
                  >
                    BillBot
                  </a>
                  <p className="text-sm sm:text-base text-neutral-400">— From text to invoice in a snap.</p>
                </div>
              </div> */}

              {/* Social Icons */}
              <div className="flex items-center justify-start space-x-4 mb-4">
                {socials.map(({ href, Icon }, idx) => (
                  <a key={idx} href={href} target="_blank" rel="noopener noreferrer">
                    <Icon className="size-5 sm:size-6 hover:scale-110 transition-all duration-300 text-neutral-300 hover:text-white" />
                  </a>
                ))}
              </div>
            </div>
          </div>

          {/* Desktop Layout (lg and up) */}
          <div className="hidden lg:grid lg:grid-cols-3 gap-8 xl:gap-12 items-start">
            {/* LEFT Column */}
            <div className="flex flex-col justify-start items-start text-left space-y-6">
              <div className="space-y-4">
                <p className="text-lg xl:text-xl font-medium text-neutral-300 leading-8">
                  I'm an <span className="px-3 py-1 rounded-3xl bg-white/30 backdrop-blur-lg text-neutral-900">Engineer</span> fascinated by the art of system design and databases.
                </p>
                <p className="text-lg xl:text-xl font-semibold text-neutral-400 leading-8">
                  2x Full Stack Developer Intern&nbsp;|&nbsp;3x Hackathon Winner
                </p>
              </div>

              <div className="pt-4">
                <p className="text-lg xl:text-2xl text-neutral-100 font-medium mb-3">Prev Works</p>
                <div className="flex items-center">
                  <a
                    href="https://github.com/ChandanKhamitkar/BillBot"
                    className="underline underline-offset-4 font-semibold text-neutral-100 mr-2 text-sm xl:text-base"
                    target="_blank"
                    rel="noopener noreferrer"
                  >
                    BillBot
                  </a>
                  <p className="text-base xl:text-lg text-neutral-400">— From text to invoice in a snap.</p>
                </div>
              </div>

              {/* Social Icons */}
              <div className="flex items-center space-x-3 xl:space-x-4 pt-4">
                {socials.map(({ href, Icon }, idx) => (
                  <a key={idx} href={href} target="_blank" rel="noopener noreferrer">
                    <Icon className="size-4 lg:size-5 xl:size-7 hover:scale-110 transition-all duration-300 text-neutral-300 hover:text-white" />
                  </a>
                ))}
              </div>
            </div>

            {/* CENTER Column */}
            <div className="relative flex justify-center self-end">
              {/* Circle behind profile */}
              <div className="absolute flex items-center justify-center pointer-events-none z-15">
                <div className="w-[500px] h-[500px] xl:w-[600px] xl:h-[600px] bg-black/20 rounded-full backdrop-blur-md translate-y-[22%]"></div>
              </div>

              {/* Profile image */}
              <div className="w-[320px] xl:w-[420px] aspect-[3/4] flex items-end overflow-hidden relative z-25 translate-y-[10%]">
                <img
                  src="me.png"
                  alt="Chandan Khamitkar's Profile Pic"
                  className="w-full h-full object-contain object-bottom "
                />
              </div>
            </div>

            {/* RIGHT Column */}
            <div className="flex flex-col justify-start items-end text-right space-y-6">
              <p className="text-lg xl:text-xl font-medium text-neutral-300 leading-8">
                The more rooted in the core, the better.
              </p>
              <p className="text-2xl xl:text-4xl font-medium italic text-neutral-200 leading-9">
                <span className="text-5xl xl:text-6xl align-[-0.2em]">" </span>
                Design for scale.<br />Build for clarity.
              </p>
            </div>
          </div>
        </div>
      </div>

      <div className="py-10"></div>
    </div >
  );
}