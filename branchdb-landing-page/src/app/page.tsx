{/* Background Video */ }
{/* <video
  autoPlay
  loop
  muted
  playsInline
  className="absolute inset-0 w-full h-full object-cover z-0 blur-lg"
>
  <source src="bg-2.mp4" type="video/mp4" />
</video> */}
{/* <div className="absolute inset-0 bg-black/60 z-10"></div> */ }
// from-[#ff8c33] via-[#fe6a00] to-[#ff8c33] 
import { onest } from "./layout";

export default function Home() {
  return (
    <div className={`h-screen w-full bg-black flex flex-col overflow-x-hidden overflow-y-scroll custom-scrollbar rounded-md relative ${onest.className}`}>

      {/* Background Image */}
      <img
        src="orange-half-bottom-circle.avif"
        alt=""
        className="absolute inset-0 w-full h-full object-cover object-bottom z-0"
      />
      <div className="absolute inset-0 bg-black/40 z-10"></div>

      {/* Main content */}
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
  );
}


//   <div className="font-sans grid grid-rows-[20px_1fr_20px] items-center justify-items-center min-h-screen p-8 pb-20 gap-16 sm:p-20">
//     <div className="flex gap-4 items-center flex-col sm:flex-row">
//         <a
//           className="rounded-full border border-solid border-transparent transition-colors flex items-center justify-center bg-foreground text-background gap-2 hover:bg-[#383838] dark:hover:bg-[#ccc] font-medium text-sm sm:text-base h-10 sm:h-12 px-4 sm:px-5 sm:w-auto"
//           href="https://vercel.com/new?utm_source=create-next-app&utm_medium=appdir-template-tw&utm_campaign=create-next-app"
//           target="_blank"
//           rel="noopener noreferrer"
//         >
//           <Image
//             className="dark:invert"
//             src="/vercel.svg"
//             alt="Vercel logomark"
//             width={20}
//             height={20}
//           />
//           Deploy now
//         </a>
//         <a
//           className="rounded-full border border-solid border-black/[.08] dark:border-white/[.145] transition-colors flex items-center justify-center hover:bg-[#f2f2f2] dark:hover:bg-[#1a1a1a] hover:border-transparent font-medium text-sm sm:text-base h-10 sm:h-12 px-4 sm:px-5 w-full sm:w-auto md:w-[158px]"
//           href="https://nextjs.org/docs?utm_source=create-next-app&utm_medium=appdir-template-tw&utm_campaign=create-next-app"
//           target="_blank"
//           rel="noopener noreferrer"
//         >
//           Read our docs
//         </a>
//       </div>
// <footer className="row-start-3 flex gap-[24px] flex-wrap items-center justify-center">
//       <a
//         className="flex items-center gap-2 hover:underline hover:underline-offset-4"
//         href="https://nextjs.org/learn?utm_source=create-next-app&utm_medium=appdir-template-tw&utm_campaign=create-next-app"
//         target="_blank"
//         rel="noopener noreferrer"
//       >
//         <Image
//           aria-hidden
//           src="/file.svg"
//           alt="File icon"
//           width={16}
//           height={16}
//         />
//         Learn
//       </a>
//       <a
//         className="flex items-center gap-2 hover:underline hover:underline-offset-4"
//         href="https://vercel.com/templates?framework=next.js&utm_source=create-next-app&utm_medium=appdir-template-tw&utm_campaign=create-next-app"
//         target="_blank"
//         rel="noopener noreferrer"
//       >
//         <Image
//           aria-hidden
//           src="/window.svg"
//           alt="Window icon"
//           width={16}
//           height={16}
//         />
//         Examples
//       </a>
//       <a
//         className="flex items-center gap-2 hover:underline hover:underline-offset-4"
//         href="https://nextjs.org?utm_source=create-next-app&utm_medium=appdir-template-tw&utm_campaign=create-next-app"
//         target="_blank"
//         rel="noopener noreferrer"
//       >
//         <Image
//           aria-hidden
//           src="/globe.svg"
//           alt="Globe icon"
//           width={16}
//           height={16}
//         />
//         Go to nextjs.org →
//       </a>
//     </footer>
// </div>