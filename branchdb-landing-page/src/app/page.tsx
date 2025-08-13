import { cookedData, mainPageData } from "@/lib/mainPageData";
import { onest } from "./layout";
import { div } from "motion/react-client";

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
            Branch DB
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

      {/* Section-3 */}
      <div className="mt-12 flex justify-center items-stretch gap-6 h-max">
        {
          mainPageData.map((item, index) => <div key={index} className="flex flex-col justify-start items-start bg-neutral-950/30 border border-neutral-400/20 rounded-2xl p-6 relative w-96 overflow-clip">
            <img src="dots.svg" alt="Key Value icon" className="absolute w-full h-full object-cover inset-0 z-0 opacity-[7%]" />
            <div className="absolute inset-0 w-full hull bg-gradient-to-t from-black to-transparent"></div>

            <p className="text-3xl font-medium text-white drop-shadow-xl">{item.title}</p>
            <p className="text-sx font-light text-neutral-400 drop-shadow-xl mt-6">{item.desc}</p>
          </div>)
        }
      </div>

      {/* Section-4 */}
      <div className="py-20 w-full flex flex-col justify-center items-center">
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
                <p className="text-sm font-light text-neutral-400 drop-shadow-xl mt-4">
                  {item.desc}
                </p>
              </div>
            </div>
          ))}
        </div>
      </div>

    </div >
  );
}