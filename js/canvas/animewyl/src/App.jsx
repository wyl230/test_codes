import { useState } from 'react'
import reactLogo from './assets/react.svg'
import viteLogo from '/vite.svg'
import './App.css'
import anime from 'animejs/lib/anime.es.js';


function App() {
  const [count, setCount] = useState(0);
  (function() {

    // Variables to use later
    var rangeWrapper = document.querySelector('.range__wrapper');
    var rangeInput = document.querySelector('.range__input');
    var rangeValues = document.querySelector('.range__values');
    var rangeValueNumberTop = document.querySelector('.range__value__number--top');
    var rangeValueNumberBottom = document.querySelector('.range__value__number--bottom');
    var rangeSliderPaths = document.querySelectorAll('.range__slider__path');
    var mouseX = 0;
    var mouseY = 0;
    var mouseInitialY = 0;
    var mouseDy = 0;
    var mouseDyLimit = 150;
    var mouseDyFactor = 3;
    var max = 100;
    var rangeMin = parseInt(rangeInput.min);
    var rangeMax = parseInt(rangeInput.max);
    var rangeValue = parseInt(rangeInput.value);
    var rangeHeight = 480;
    var currentY = rangeHeight * rangeValue / max;
    var rangeMinY = rangeHeight * rangeMin / max;
    var rangeMaxY = rangeHeight * rangeMax / max;
    var scaleMax = 0.32;
    var scale, newPath, newY, newSliderY, lastMouseDy, rangeWrapperLeft, pageX, pageY;

    // Update slider value, initially using the `input` value
    updateValue();

    // Function to build the slider `path`, using the given `dy` and `ty` values
    function buildPath(dy, ty) {
      return 'M 0 ' + ty + ' q ' + mouseX + ' ' + dy + ' 320 0 l 0 480 l -320 0 Z';
    }

    // Function to update the slider value
    function updateValue() {
      // Clear animations if are still running
      anime.remove([rangeValues, rangeSliderPaths[0], rangeSliderPaths[1]]);

      // Calc the `input` value using the current `y`
      rangeValue = parseInt(currentY * max / rangeHeight);
      // Calc `scale` value for numbers
      scale = (rangeValue - rangeMin) / (rangeMax - rangeMin) * scaleMax;
      // Update `input` value
      rangeInput.value = rangeValue;
      // Update numbers values
      rangeValueNumberTop.innerText = max - rangeValue;
      rangeValueNumberBottom.innerText = rangeValue;
      // Translate range values
      rangeValues.style.transform = 'translateY(' + (rangeHeight - currentY) + 'px)';
      // Apply corresponding `scale` to numbers
      rangeValueNumberTop.style.transform = 'scale(' + (1 - scale) + ')';
      rangeValueNumberBottom.style.transform = 'scale(' + (1 - (scaleMax - scale)) + ')';

      // Some maths calc
      if (Math.abs(mouseDy) < mouseDyLimit) {
        lastMouseDy = mouseDy;
      } else {
        lastMouseDy = mouseDy < 0 ? -mouseDyLimit : mouseDyLimit;
      }

      // Calc the `newSliderY` value to build the slider `path`
      newSliderY = currentY + lastMouseDy / mouseDyFactor;
      if (newSliderY < rangeMinY || newSliderY > rangeMaxY) {
        newSliderY = newSliderY < rangeMinY ? rangeMinY : rangeMaxY;
      }

      // Build `path` string and update `path` elements
      newPath = buildPath(lastMouseDy, rangeHeight - newSliderY);
      rangeSliderPaths[0].setAttribute('d', newPath);
      rangeSliderPaths[1].setAttribute('d', newPath);
    }

    // Function to simulate the elastic behavior
    function elasticRelease() {
      // Morph the paths to the opposite direction, to simulate a strong elasticity
      anime({
        targets: rangeSliderPaths,
        d: buildPath(-lastMouseDy * 1.3, rangeHeight - (currentY - lastMouseDy / mouseDyFactor)),
        duration: 150,
        easing: 'linear',
        complete: function() {
          // Morph the paths to the normal state, using the `elasticOut` easing function (default)
          anime({
            targets: rangeSliderPaths,
            d: buildPath(0, rangeHeight - currentY),
            duration: 4000,
            elasticity: 880
          });
        }
      });

      // Translate the values to the opposite direction, to simulate a strong elasticity
      anime({
        targets: rangeValues,
        translateY: rangeHeight - (currentY + lastMouseDy / mouseDyFactor / 4),
        duration: 150,
        easing: 'linear',
        complete: function() {
          // Translate the values to the right position, using the `elasticOut` easing function (default)
          anime({
            targets: rangeValues,
            translateY: rangeHeight - currentY,
            duration: 4000,
            elasticity: 880
          });
        }
      });
    }

    // Handle `mousedown` and `touchstart` events, saving data about mouse position
    function mouseDown(e) {
      mouseY = mouseInitialY = e.targetTouches ? e.targetTouches[0].pageY : e.pageY;
      rangeWrapperLeft = rangeWrapper.getBoundingClientRect().left;
    }

    // Handle `mousemove` and `touchmove` events, calculating values to morph the slider `path` and translate values properly
    function mouseMove(e) {
      if (mouseY) {
        pageX = e.targetTouches ? e.targetTouches[0].pageX : e.pageX;
        pageY = e.targetTouches ? e.targetTouches[0].pageY : e.pageY;
        mouseX = pageX - rangeWrapperLeft;
        mouseDy = (pageY - mouseInitialY) * mouseDyFactor;
        newY = currentY + mouseY - pageY;
        if (newY >= rangeMinY && newY <= rangeMaxY) {
          currentY = newY;
          mouseY = pageY;
        } else {
          currentY = newY < rangeMinY ? rangeMinY : rangeMaxY;
        }
        // After doing maths, update the value
        updateValue();
      }
    }

    // Handle `mouseup`, `mouseleave` and `touchend` events
    function mouseUp() {
      // Trigger elastic animation in case `y` value has changed
      if (mouseDy) {
        elasticRelease();
      }
      // Reset values
      mouseY = mouseDy = 0;
    }

    // Events listeners
    rangeWrapper.addEventListener('mousedown', mouseDown);
    rangeWrapper.addEventListener('touchstart', mouseDown);
    rangeWrapper.addEventListener('mousemove', mouseMove);
    rangeWrapper.addEventListener('touchmove', mouseMove);
    rangeWrapper.addEventListener('mouseup', mouseUp);
    rangeWrapper.addEventListener('mouseleave', mouseUp);
    rangeWrapper.addEventListener('touchend', mouseUp);

  })()

  return (
    <>
      <div class="range__wrapper">
        <input class="range__input" type="range" min="30" max="70" value="64" />

        <svg class="range__slider" width="320px" height="480px" viewBox="0 0 320 480">
          <defs>
            <symbol id="range__marks" shape-rendering="crispEdges">
              <path class="range__marks__path" d="M 257 30 l 33 0"></path>
              <path class="range__marks__path" d="M 268 60 l 22 0"></path>
              <path class="range__marks__path" d="M 278 90 l 12 0"></path>
              <path class="range__marks__path" d="M 278 120 l 12 0"></path>
              <path class="range__marks__path" d="M 278 150 l 12 0"></path>
              <path class="range__marks__path" d="M 278 180 l 12 0"></path>
              <path class="range__marks__path" d="M 278 210 l 12 0"></path>
              <path class="range__marks__path" d="M 278 240 l 12 0"></path>
              <path class="range__marks__path" d="M 278 270 l 12 0"></path>
              <path class="range__marks__path" d="M 278 300 l 12 0"></path>
              <path class="range__marks__path" d="M 278 330 l 12 0"></path>
              <path class="range__marks__path" d="M 278 360 l 12 0"></path>
              <path class="range__marks__path" d="M 278 390 l 12 0"></path>
              <path class="range__marks__path" d="M 268 420 l 22 0"></path>
              <path class="range__marks__path" d="M 257 450 l 33 0"></path>
            </symbol>
            <clipPath id="range__slider__clip-path">
              <path class="range__slider__path" d="M 0 480 l 320 0 l 0 480 l -320 0 Z"></path>
            </clipPath>
          </defs>
          <use xlink: href="#range__marks" class="range__marks__pink"></use>
          <path class="range__slider__path" d="M 0 480 l 320 0 l 0 480 l -320 0 Z"></path>
          <use xlink: href="#range__marks" class="range__marks__white" clip-path="url(#range__slider__clip-path)"></use>
        </svg>

        <div class="range__values">
          <div class="range__value range__value--top">
            <span class="range__value__number range__value__number--top"></span>
            <span class="range__value__text range__value__text--top">
              <span>Points</span>
              <span>You Need</span>
            </span>
          </div>
          <div class="range__value range__value--bottom">
            <span class="range__value__number range__value__number--bottom"></span>
            <span class="range__value__text range__value__text--bottom">
              <span>Points</span>
              <span>You Have</span>
            </span>
          </div>
        </div>
      </div>
    </>
  )
}

export default App

